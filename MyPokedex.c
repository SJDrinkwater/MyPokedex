#include<stdlib.h>
#include<string.h>
#include<stdio.h>

///////////////// STRUCTURES////////////////

// Pokedex struct
struct Pokedex {
    struct PlayerNode *player_list;
    struct PokemonNode *pokemon_list;
};

// PokemonNode struct
struct PokemonNode {
    char name[20];
    char type[20];
    char ability[20];
    struct PokemonNode *next;
};

// PlayerNode struct
struct PlayerNode {
    char name[20];
    int pokemon_count;
    struct PokemonNode* PokemonArray[20];
    struct PlayerNode *next;
};

///////////////// STRUCTURES////////////////



///////////////// POKEMON LIST FUNCTIONS////////////////

// Function to create a new PokemonNode
struct PokemonNode* NewPokemonNode(char *name, char *type, char *ability) {
    struct PokemonNode* new_node = (struct PokemonNode*) malloc(sizeof(struct PokemonNode));
    strcpy(new_node->name, name);
    strcpy(new_node->type, type);
    strcpy(new_node->ability, ability);
    new_node->next = NULL;
    return new_node;
}

// Function to add a PokemonNode to the list
void AddPokemonToList(struct Pokedex *pokedex, char *name, char *type, char *ability) {
    struct PokemonNode* new_node = NewPokemonNode(name, type, ability);
    struct PokemonNode* current = pokedex->pokemon_list;
    if (current == NULL) {
        pokedex->pokemon_list = new_node;
    } else {
        while (current->next != NULL) {
            if (strcmp(current->name, name) == 0) {
                return 0;
            }
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to find a specific PokemonNode by name
struct PokemonNode* FindPokemon(struct Pokedex *pokedex, char *name) {
    struct PokemonNode *current = pokedex->pokemon_list;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

///////////////// POKEMON LIST FUNCTIONS////////////////



///////////////// PLAYER LIST FUNCTIONS////////////////

// Function to create a new PlayerNode
struct PlayerNode* NewPlayerNode(char *name) {
    struct PlayerNode* new_node = (struct PlayerNode*) malloc(sizeof(struct PlayerNode));
    strcpy(new_node->name, name);
    new_node->pokemon_count = 0;
    new_node->next = NULL;
    return new_node;
}

// Function to add a PlayerNode to the list
void AddPlayerToList(struct Pokedex *pokedex, char *name) {
    struct PlayerNode* new_node = NewPlayerNode(name);
    struct PlayerNode* current = pokedex->player_list;

    if (current == NULL) {
        pokedex->player_list = new_node; 
    } else {
        while (current->next != NULL) { 
            if (strcmp(current->name, name) == 0) {
                return 0; 
            }
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to find a specific PlayerNode by name
struct PlayerNode* FindPlayer(struct Pokedex *pokedex, char *name) {
    struct PlayerNode *current = pokedex->player_list;
    while (current != NULL) {   
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

///////////////// PLAYER LIST FUNCTIONS////////////////



// Function to add pokemon to a specific player
void AddPokemonToPlayer(struct Pokedex *pokedex, char *player_name, char *pokemon_name) {
    // Find the player
    struct PlayerNode *player = FindPlayer(pokedex, player_name);
    if (player == NULL) {
        printf("Player not found\n");
        return;
    }
    // Find the Pokemon
    struct PokemonNode *pokemon = FindPokemon(pokedex, pokemon_name);
    if (pokemon == NULL) {
        printf("Pokemon not found\n");
        return;
    }
    // check if the pokemon is already captured by the player
    for (int i = 0; i < player->pokemon_count; i++) {
        if (player->PokemonArray[i] == pokemon) {
            printf("This Pokemon is already captured by the player\n");
            return;
        }
    }
    // add the pokemon to the player's list and increment the count
    player->PokemonArray[player->pokemon_count] = pokemon;
    player->pokemon_count++;
    printf("%s has been added to the player %s's list\n",pokemon_name,player_name);
}



///////////////// DISPLAY FUNCTIONS////////////////

// Function to display the details of a specific Pokemon
void DisplayPokemonDetails(struct Pokedex *pokedex, char *name) {
    struct PokemonNode *pokemon = FindPokemon(pokedex, name);
    if (pokemon == NULL) {
        printf("Pokemon not found.\n");
        return;
    }
    printf("Name: %s\nType: %s\nAbility: %s\n", pokemon->name, pokemon->type, pokemon->ability);
}

//Function to display the player name, amount of pokemon a player owns and the pokemon they own
void DisplayPlayerDetails(struct Pokedex *pokedex, char *name) {
    struct PlayerNode *player = FindPlayer(pokedex, name);
    if (player == NULL) {
        printf("Player not found.\n");
        return;
    }
    printf("Name: %s\nPokemon owned: %d\n", player->name, player->pokemon_count);
    printf("Pokemon: ");
    for (int i = 0; i < player->pokemon_count; i++) {
        printf("%s ", player->PokemonArray[i]->name);
    }
    printf("\n");
}

//Function to list all pokemon in the list
void ListPokemon(struct Pokedex *pokedex) {
    struct PokemonNode *current = pokedex->pokemon_list;
    printf("\nOur Current Pokemon Are:\n");
    while (current != NULL) {
        printf("%s\n", current->name);

        current = current->next;
    }
}

//Function to list all player in the list
void ListPlayers(struct Pokedex *pokedex) {
    struct PlayerNode *current = pokedex->player_list;
    printf("\nOur Current Players Are:\n");
    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}

///////////////// DISPLAY FUNCTIONS////////////////



int main() {
    struct Pokedex pokedex;
    
    AddPokemonToList(&pokedex, "Venusaur","Grass","Balooen");
    AddPokemonToList(&pokedex, "Pikachu","Electric","Static");
    AddPokemonToList(&pokedex, "Bulbasaur","Grass","Overgrow");
    AddPokemonToList(&pokedex, "Ivysaur","Grass","Overgrow");
    AddPokemonToList(&pokedex, "Venusaur","Grass","Balooen");
    
    AddPlayerToList(&pokedex, "John");
    AddPlayerToList(&pokedex, "Bill");
    AddPlayerToList(&pokedex, "Emily");
    AddPlayerToList(&pokedex, "Bill");
   
    
    AddPokemonToPlayer(&pokedex, "Emily", "Pikachu");
    AddPokemonToPlayer(&pokedex, "John", "Bulbasaur");
    AddPokemonToPlayer(&pokedex, "Bill", "Ivysaur");
    AddPokemonToPlayer(&pokedex, "John", "Venusaur");
    
    
    // Main program loop
    while (1) {
        // Print menu options
        printf("\n--------------------------------");
        printf("\nWelcome To The Pokedex Main Menu");
        printf("\n--------------------------------\n");
        printf("1. List all Pokemon\n");
        printf("2. List all players\n");
        printf("3. Display Pokemon details\n");
        printf("4. Display player details\n");
        printf("5. Exit\n");
        printf("\n");
        printf("Enter your choice: ");
        printf("\n");

        // Get user input
        char pokemon_name[20];
        char player_name[20];

       
        int choice;
        scanf("%d", &choice);
        
        // Take action based on user input
        switch (choice) {
            case 1:
                ListPokemon(&pokedex);
                break;
            case 2:
                ListPlayers(&pokedex);
                break;
            case 3:
                printf("Enter the name of the Pokemon: ");
                scanf("%s", pokemon_name);
                DisplayPokemonDetails(&pokedex, pokemon_name);
                break;
            case 4:
                printf("Enter the name of the player: ");
                scanf("%s", player_name);
                DisplayPlayerDetails(&pokedex, player_name);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}
