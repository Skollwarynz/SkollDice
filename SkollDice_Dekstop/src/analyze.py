#!/usr/bin/env python3
"""
Dice Balance Analyzer
Calls ./main NUM_RUNS times, captures its stdout each time,
accumulates all dice rolls, computes balance statistics,
and exports a final CSV summary.

Debug is always ON (stderr, colored).

Usage: python analyze.py
       python analyze.py --runs 200
       python analyze.py --csv output.csv
"""

import sys
import os
import csv
import subprocess
from collections import defaultdict, Counter
from datetime import datetime

# ─────────────────────────────────────────────
#  CONSTANTS
# ─────────────────────────────────────────────
DEFAULT_RUNS = 100
WARN_THRESHOLD = 2.0  # % deviation flagged as anomaly
BAR_WIDTH = 20
DEFAULT_CSV = "dice_results.csv"
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
MAIN_EXE = os.path.join(SCRIPT_DIR, "main")

MAX_FACES = {"D4": 4, "D6": 6, "D8": 8, "D10": 10, "D12": 12, "D20": 20, "D100": 100}


# ─────────────────────────────────────────────
#  ARG PARSING
# ─────────────────────────────────────────────
def get_arg(flag: str, default: str | None = None) -> str | None:
    args = sys.argv[1:]
    if flag in args:
        idx = args.index(flag)
        if idx + 1 < len(args):
            return args[idx + 1]
    return default


def get_runs() -> int:
    val = get_arg("--runs")
    try:
        return int(val) if val else DEFAULT_RUNS
    except ValueError:
        return DEFAULT_RUNS


def get_csv_path() -> str:
    return get_arg("--csv") or DEFAULT_CSV


# ─────────────────────────────────────────────
#  DEBUG (always ON → stderr, colored)
# ─────────────────────────────────────────────
def dbg(msg: str, level: int = 0) -> None:
    indent = "  " * level
    print(f"\033[90m[DBG]{indent} {msg}\033[0m", file=sys.stderr, flush=True)


def dbg_section(title: str) -> None:
    pad = "─" * (len(title) + 4)
    print(f"\033[36m\n[DBG] ┌{pad}┐\033[0m", file=sys.stderr)
    print(f"\033[36m[DBG] │  {title}  │\033[0m", file=sys.stderr)
    print(f"\033[36m[DBG] └{pad}┘\033[0m", file=sys.stderr, flush=True)


def dbg_progress(current: int, total: int) -> None:
    pct = current / total
    filled = round(pct * 30)
    bar = "█" * filled + "░" * (30 - filled)
    print(
        f"\r\033[90m[DBG]  Runs [{bar}] {current}/{total}  ({pct*100:.0f}%)\033[0m",
        end="",
        file=sys.stderr,
        flush=True,
    )
    if current == total:
        print(file=sys.stderr)


# ─────────────────────────────────────────────
#  OUTPUT PARSING
# ─────────────────────────────────────────────
def parse_output(raw: str) -> dict[str, list[int]]:
    """
    Parses ./main stdout like:
        D6: 2 4 5 1 5 6 2 2 3 5
    Returns {"D6": [2, 4, 5, 1, 5, 6, 2, 2, 3, 5], ...}
    """
    result: dict[str, list[int]] = {}
    for line in raw.strip().splitlines():
        line = line.strip()
        if not line or ":" not in line:
            continue
        label, _, values = line.partition(":")
        label = label.strip().upper()
        try:
            nums = [int(x) for x in values.split() if x.strip()]
            if nums:
                result[label] = nums
        except ValueError:
            pass
    return result


# ─────────────────────────────────────────────
#  CALL ./main ONCE
# ─────────────────────────────────────────────
def call_main(run_index: int) -> dict[str, list[int]] | None:
    """
    Spawns ./main, captures stdout, returns parsed dice rolls.
    Returns None if the process fails.
    """
    try:
        proc = subprocess.run(
            [MAIN_EXE],
            capture_output=True,
            text=True,
            timeout=30,
        )
        if proc.returncode != 0:
            dbg(
                f"Run {run_index:>3}: ./main exited with code {proc.returncode}",
                level=1,
            )
            dbg(f"stderr: {proc.stderr.strip()[:120]}", level=2)
            return None

        parsed = parse_output(proc.stdout)
        if not parsed:
            dbg(f"Run {run_index:>3}: output empty or unparseable", level=1)
            dbg(f"raw stdout: {repr(proc.stdout[:120])}", level=2)
            return None

        dbg(
            f"Run {run_index:>3}: captured → "
            + "  ".join(f"{k}:{len(v)}rolls" for k, v in parsed.items()),
            level=1,
        )
        return parsed

    except subprocess.TimeoutExpired:
        dbg(f"Run {run_index:>3}: TIMEOUT", level=1)
        return None
    except FileNotFoundError:
        print(f"\nERROR: '{MAIN_EXE}' not found.", file=sys.stderr)
        print(
            "Make sure the 'main' executable is in the same folder as this script.",
            file=sys.stderr,
        )
        sys.exit(1)


# ─────────────────────────────────────────────
#  ACCUMULATOR
# ─────────────────────────────────────────────
def collect_all_runs(num_runs: int) -> tuple[dict[str, Counter], int]:
    """
    Calls ./main num_runs times.
    Returns (accumulated_counts, successful_runs).
    accumulated_counts = {"D6": Counter({1: 432, 2: 389, ...}), ...}
    """
    dbg_section("COLLECTION PHASE")
    dbg(f"Executable : {MAIN_EXE}")
    dbg(f"Runs       : {num_runs}")

    # die_label → face → total count across all runs
    accumulated: dict[str, Counter] = defaultdict(Counter)
    success = 0

    for i in range(1, num_runs + 1):
        dbg_progress(i, num_runs)
        run_data = call_main(i)
        if run_data is None:
            continue
        for die, rolls in run_data.items():
            accumulated[die].update(rolls)
        success += 1

    print()  # newline after progress bar
    dbg(f"Successful runs : {success}/{num_runs}")

    if success == 0:
        print("ERROR: all runs failed.", file=sys.stderr)
        sys.exit(1)

    # log totals
    dbg_section("ACCUMULATED TOTALS")
    for die in sorted(accumulated):
        total = sum(accumulated[die].values())
        dbg(f"{die}: {total} total rolls collected")
        for face in sorted(accumulated[die]):
            dbg(f"  face {face:>3}: {accumulated[die][face]:>7} rolls", level=1)

    return accumulated, success


# ─────────────────────────────────────────────
#  STATISTICS
# ─────────────────────────────────────────────
def compute_stats(counts: Counter, max_face: int) -> dict[int, float]:
    """
    Converts raw counts to percentage per face.
    Returns {face: percentage, ...}
    """
    total = sum(counts.values())
    return {
        face: (counts.get(face, 0) / total * 100.0) if total else 0.0
        for face in range(1, max_face + 1)
    }


def chi_square(pct: dict[int, float], label: str) -> tuple[float, str]:
    """Chi-square goodness-of-fit vs. uniform distribution (α=0.05)."""
    n = len(pct)
    expected = 100.0 / n
    chi2 = sum((p - expected) ** 2 / expected for p in pct.values())
    critical = {3: 7.81, 5: 11.07, 7: 14.07, 9: 16.92, 11: 19.68, 19: 30.14, 99: 123.22}
    df = n - 1
    crit = critical.get(df, 3.841 * df)
    verdict = "BALANCED" if chi2 <= crit else "UNBALANCED"

    dbg(f"{label}: χ²={chi2:.4f}  critical={crit:.4f}  df={df}  → {verdict}", level=1)
    return chi2, verdict


# ─────────────────────────────────────────────
#  TERMINAL TABLE
# ─────────────────────────────────────────────
def draw_bar(pct: float, expected: float) -> str:
    filled = round(pct / 100 * BAR_WIDTH)
    e_pos = round(expected / 100 * BAR_WIDTH)
    b = ["─"] * BAR_WIDTH
    if 0 <= e_pos < BAR_WIDTH:
        b[e_pos] = "┼"
    for i in range(min(filled, BAR_WIDTH)):
        b[i] = "█" if i != e_pos else "▓"
    return "".join(b)


def print_table(
    label: str,
    max_face: int,
    pct: dict[int, float],
    counts: Counter,
    chi2: float,
    verdict: str,
    num_runs: int,
) -> None:
    expected = 100.0 / max_face
    icon = "✅" if verdict == "BALANCED" else "⚠️ "
    total_rolls = sum(counts.values())

    sep = "═" * 76
    print(f"\n╔{sep}╗")
    title = f"  {label}  (faces 1–{max_face})   {icon} {verdict}   χ²={chi2:.3f}"
    print(f"║{title:<76}║")
    print(f"╠{sep}╣")
    print(
        f"║  {'Face':>6}  │  {'Total Rolls':>11}  │  {'Pct%':>7}  │  {'Expected%':>9}  │  {'Δ%':>6}  │  {'Distribution':<18}  ║"
    )
    print(f"╠{'─'*76}╣")

    for face in range(1, max_face + 1):
        n = counts.get(face, 0)
        p = pct.get(face, 0.0)
        delta = p - expected
        flag = "  " if abs(delta) < WARN_THRESHOLD else "⚠️"
        b = draw_bar(p, expected)
        print(
            f"║  {face:>6}  │  {n:>11,}  │  {p:>6.2f}%  │  {expected:>8.2f}%  │  {delta:>+5.2f}%{flag}│  {b}  ║"
        )

    print(f"╠{'─'*76}╣")
    print(
        f"║  Total rolls collected: {total_rolls:>10,}   from {num_runs} runs   {'│ ┼ = uniform expected':>22}  ║"
    )
    print(f"╚{sep}╝")


# ─────────────────────────────────────────────
#  CSV EXPORT
# ─────────────────────────────────────────────
FIELDNAMES = [
    "timestamp",
    "die",
    "total_faces",
    "face",
    "total_rolls",
    "simulated_pct",
    "expected_pct",
    "delta_pct",
    "chi2",
    "balance",
    "anomaly_flag",
]


def export_csv(all_rows: list[dict], csv_path: str) -> None:
    dbg_section("CSV EXPORT")
    file_exists = os.path.isfile(csv_path)
    mode = "a" if file_exists else "w"
    dbg(f"Path  : {os.path.abspath(csv_path)}", level=1)
    dbg(
        f"Mode  : '{mode}'  (file {'exists → appending' if file_exists else 'is new → creating'})",
        level=1,
    )
    dbg(f"Rows  : {len(all_rows)}", level=1)

    with open(csv_path, mode, newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=FIELDNAMES)
        if not file_exists:
            writer.writeheader()
            dbg("Header written", level=1)
        writer.writerows(all_rows)

    action = "updated" if file_exists else "created"
    print(f"\n  📄  CSV {action}: {os.path.abspath(csv_path)}")
    print(f"       Rows written : {len(all_rows)}")


def build_csv_rows(
    label: str,
    max_face: int,
    pct: dict[int, float],
    counts: Counter,
    chi2: float,
    verdict: str,
    ts: str,
) -> list[dict]:
    expected = 100.0 / max_face
    rows = []
    for face in range(1, max_face + 1):
        p = pct.get(face, 0.0)
        delta = p - expected
        rows.append(
            {
                "timestamp": ts,
                "die": label,
                "total_faces": max_face,
                "face": face,
                "total_rolls": counts.get(face, 0),
                "simulated_pct": round(p, 4),
                "expected_pct": round(expected, 4),
                "delta_pct": round(delta, 4),
                "chi2": round(chi2, 4),
                "balance": verdict,
                "anomaly_flag": "YES" if abs(delta) >= WARN_THRESHOLD else "NO",
            }
        )
    dbg(f"Built {len(rows)} rows for {label}", level=1)
    return rows


# ─────────────────────────────────────────────
#  MAIN
# ─────────────────────────────────────────────
CANONICAL_ORDER = ["D4", "D6", "D8", "D10", "D12", "D20", "D100"]


def main() -> None:
    num_runs = get_runs()
    csv_path = get_csv_path()

    print("┌──────────────────────────────────────────────────────┐")
    print("│   🎲  DICE BALANCE ANALYZER  🎲                      │")
    print(f"│   Executable : {MAIN_EXE:<40}│")
    print(f"│   Runs       : {num_runs:<40}│")
    print(f"│   CSV output : {csv_path:<40}│")
    print(f"│   Debug      : ON (stderr)                           │")
    print("└──────────────────────────────────────────────────────┘\n")

    dbg_section("STARTUP")
    dbg(f"argv      : {sys.argv}")
    dbg(f"num_runs  : {num_runs}")
    dbg(f"csv_path  : {csv_path}")
    dbg(f"main exe  : {MAIN_EXE}  exists={os.path.isfile(MAIN_EXE)}")

    # ── phase 1: collect rolls from ./main ──────────────────────
    print(f"  ⏳  Calling ./main {num_runs} times…\n", flush=True)
    accumulated, successful_runs = collect_all_runs(num_runs)

    # ── phase 2: compute stats and print tables ──────────────────
    dbg_section("STATISTICS & TABLES")

    keys = [k for k in CANONICAL_ORDER if k in accumulated]
    keys += [k for k in accumulated if k not in CANONICAL_ORDER]

    ts: str = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    all_csv_rows: list[dict] = []

    for label in keys:
        counts = accumulated[label]
        max_face = MAX_FACES.get(label, max(counts.keys()))
        pct = compute_stats(counts, max_face)
        chi2, verdict = chi_square(pct, label)
        print_table(label, max_face, pct, counts, chi2, verdict, successful_runs)
        all_csv_rows.extend(
            build_csv_rows(label, max_face, pct, counts, chi2, verdict, ts)
        )

    # ── phase 3: export CSV ──────────────────────────────────────
    export_csv(all_csv_rows, csv_path)

    dbg_section("DONE")
    dbg(f"Total CSV rows : {len(all_csv_rows)}")
    dbg(f"Timestamp      : {ts}")
    print("\n  ✔  Analysis complete.")


if __name__ == "__main__":
    main()
