#include "../include/src.h"

// The maximum number of character is actually 2000 but the 50 are for eventual errors
#define MAX_MESSAGE 1950

FILE* rand_reader = NULL;
Dices types_and_number_of_dices[7] = {
    {0, D4},  {0, D6},  {0, D8},  {0, D10},
    {0, D12}, {0, D20}, {0, D100}
};

void parse_and_calculate(char** request, struct discord *client, const struct discord_message *event){
  char* token;
  int requests = 1;
  while ((token = strtok_r(NULL, ", ", request)) && requests < 8){
      int number, position;
      if(sscanf(token, "%dd%d",&number, &position)!= 2){
          struct discord_create_message params = { .content = "ERROR input not accetable, correct and retry" };
          CCORDcode code = discord_create_message(client, event->channel_id, &params, NULL);
          return;
      }
      char error[30];
      CCORDcode code;
      switch (position) {
          case 4:
            if(types_and_number_of_dices[0].n == 0)
              types_and_number_of_dices[0].n = number;
            else{
              snprintf(error, sizeof(error), "ERROR the D%d was already setted !!\n", position);
              struct discord_create_message params = { .content = error };
              code = discord_create_message(client, event->channel_id, &params, NULL);
              if (code != CCORD_OK){ //Error handling 
                discord_strerror(code, client);
                return;
              }
            }
            break;
          case 6:
            if(types_and_number_of_dices[1].n == 0)
              types_and_number_of_dices[1].n = number;
            else{
              snprintf(error, sizeof(error), "ERROR the D%d was already setted !!\n", position);
              struct discord_create_message params = { .content = error };
              code = discord_create_message(client, event->channel_id, &params, NULL);
              if (code != CCORD_OK){ //Error handling 
                discord_strerror(code, client);
                return;
              }
            }
            break;
          case 8:
            if(types_and_number_of_dices[2].n == 0)
              types_and_number_of_dices[2].n = number;
            else{
              snprintf(error, sizeof(error), "ERROR the D%d was already setted !!\n", position);
              struct discord_create_message params = { .content = error };
              code = discord_create_message(client, event->channel_id, &params, NULL);
              if (code != CCORD_OK){ //Error handling 
                discord_strerror(code, client);
                return;
              }
            }
            break;
          case 10:
            if(types_and_number_of_dices[3].n == 0)
              types_and_number_of_dices[3].n = number;
            else{
              snprintf(error, sizeof(error), "ERROR the D%d was already setted !!\n", position);
              struct discord_create_message params = { .content = error };
              code = discord_create_message(client, event->channel_id, &params, NULL);
              if (code != CCORD_OK){ //Error handling 
                discord_strerror(code, client);
                return;
              } 
            }
            break;
          case 12:
            if(types_and_number_of_dices[4].n == 0)
              types_and_number_of_dices[4].n = number;
            else{
              snprintf(error, sizeof(error), "ERROR the D%d was already setted !!\n", position);
              struct discord_create_message params = { .content = error };
              code = discord_create_message(client, event->channel_id, &params, NULL);
              if (code != CCORD_OK){ //Error handling 
                discord_strerror(code, client);
                return;
              }
            }
            break;
          case 20:
            if(types_and_number_of_dices[5].n == 0)
              types_and_number_of_dices[5].n = number;
            else{
              snprintf(error, sizeof(error), "ERROR the D%d was already setted !!\n", position);
              struct discord_create_message params = { .content = error };
              code = discord_create_message(client, event->channel_id, &params, NULL);
              if (code != CCORD_OK){ //Error handling 
                discord_strerror(code, client);
                return;
              }
            }
            break;
          case 100:
            if(types_and_number_of_dices[6].n == 0)
              types_and_number_of_dices[6].n = number;
            else{
              snprintf(error, sizeof(error), "ERROR the D%d was already setted !!\n", position);
              struct discord_create_message params = { .content = error };
              code = discord_create_message(client, event->channel_id, &params, NULL);
              if (code != CCORD_OK){ //Error handling 
                discord_strerror(code, client);
                return;
              }
            }
            break;
          default: 
            snprintf(error, sizeof(error), "ERROR the D%d doesn't exist!!\n", position);
            struct discord_create_message params = { .content = error };
            code = discord_create_message(client, event->channel_id, &params, NULL);
            if (code != CCORD_OK){ //Error handling 
              discord_strerror(code, client);
              return;
            }
      }
      requests++;
  }
  //to implement the response there is a simple dynamic string setup
  int capacity = 256;
  char *response = malloc(capacity);
  *response = '\0';
  char buffer [20] = "";  
  int index_response = 0;
  //logic of dices generation 
  int index_dices = 0;
  while (index_dices < 7) {
    int number_of_generations = types_and_number_of_dices[index_dices].n;
    if (number_of_generations > 0) {
      snprintf(buffer, sizeof(buffer), "D%d: ", types_and_number_of_dices[index_dices].dices_type);
      strcat(response, buffer);
      //reset the dice for next message
      types_and_number_of_dices[index_dices].n = 0;
    for (int i = 0; i < number_of_generations; i++) {
      int value = simple_discard_method(
            types_and_number_of_dices[index_dices].dices_type, rand_reader);
       // this is the moment of resize, the program start to resize when an addition of 4 letter is impossible 
       // so when the longest string is generated ("100 ") the string is ready and has space to spare
      if(capacity <= index_response + 4 && (capacity < MAX_MESSAGE)){
         response = reallocarray(response, capacity+256, sizeof(char)); 
         if(response == NULL){
            exit(EXIT_FAILURE);
          }
         // the increase is about 256 instead of multipling the length because is normally expected to have a low number of consecutive 
         // trhow of dices
         capacity += 256;
      } else if(index_response >= MAX_MESSAGE) {
          struct discord_create_message params = { .content = response };
          CCORDcode code = discord_create_message(client, event->channel_id, &params, NULL);
          if (code != CCORD_OK){ //Error handling 
            discord_strerror(code, client);
             return;
          }
          response[0] = '\0';
          index_response = 0;
      }
      snprintf(buffer, sizeof(buffer), "%d ", value);
      strcat(response, buffer);
      index_response += 4;
      }
     }
     index_dices++;
    if(number_of_generations > 0){
     snprintf(buffer, sizeof(buffer), "\n");
     strcat(response, buffer);
    }
    // if (code != CCORD_OK) { //Error handling 
    // discord_strerror(code, client); 
    }

    struct discord_create_message params = { .content = response };
    CCORDcode code = discord_create_message(client, event->channel_id, &params, NULL);
    if (code != CCORD_OK){ //Error handling 
      discord_strerror(code, client);
      return;
    }
return;
}
// if the user  write the full command by hand in chat
void message_receiver(struct discord *client, const struct discord_message *event){
  if(event->author->bot) return;
  char *request = strdup(event->content);
  // The code changes all upper letters into lower for an easier parse of input
  for(int i = 0; i < strlen(request); i++){
    request[i] = tolower(request[i]);
  }
  char* token;
  if(!request)
    return;
  char* saveptr;
  token = strtok_r(request, ", ", &saveptr);
  if((strcmp(token, "/roll") == 0) || (strcmp(token, "/r") == 0) )
    // the real function that parse and calculate the results
    parse_and_calculate(&saveptr, client, event);
}

void on_interaction(struct discord *client, const struct discord_interaction *event) {
    if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND) return;

    // 1. Rispondi SUBITO e CHIUDI l'interazione con un messaggio visibile
    struct discord_interaction_response ack = {
        .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
        .data = &(struct discord_interaction_callback_data){
            .content = "🎲 **Generating dices**"
        }
    };
    discord_create_interaction_response(client, event->id, event->token, &ack, NULL);

    // 2. Estrai l'input
    const char *input = "";
    if (event->data->options && event->data->options->size > 0) {
        input = event->data->options->array[0].value;
    }

    char *input_copy = strdup(input);
    if (!input_copy) return;

    char *saveptr = input_copy;

    // 3. Fake message per la tua funzione
    struct discord_message fake_msg = {
        .channel_id = event->channel_id
    };

    // 4. Invia il messaggio con i risultati del lancio
    parse_and_calculate(&saveptr, client, &fake_msg);

    free(input_copy);
}

//function for command creation when we digit "/" on Discord chat 
void on_ready(struct discord *client, const struct discord_ready *event) {

    // Definition of parameter 
    struct discord_application_command_option options[] = {
        {
            .type = DISCORD_APPLICATION_OPTION_STRING, 
            .name = "input",
            .description = "Dices of input",
            .required = true
        }
    };

    // Command creation
    struct discord_create_global_application_command roll_cmd = {
        .name = "roll",
        .description = "Generate dices results (example 1d6 10d20)",
        .options = &(struct discord_application_command_options){ 
        .size = 1,
        .array = options
        }
    };

    discord_create_global_application_command(client, event->user->id, &roll_cmd, NULL);
}

int main(){
  rand_reader = fopen("/dev/urandom", "rb");
  const char *token = getenv("DISCORD_TOKEN");
  if (!token) {
      perror("Not a valid token");
      return 1;
  }


  struct discord *client = discord_init(token);
  
  discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);

  discord_set_on_message_create(client, &message_receiver); 

  discord_set_on_ready(client, &on_ready);
  discord_set_on_interaction_create(client, &on_interaction);
  discord_run(client);

  discord_cleanup(client);
}
