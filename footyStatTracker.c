#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// initial thoughts

/* What will make this a good foot stat tracker

    - obviously, need to track:
        -> goals
        -> assists
    
    - want to use a linked list but each linked list each node should be a team and there should be an inner node of players

*/

typedef struct Stats
{
    int goals;
    int assists;
} Stats;

typedef struct Player
{
    char name[1024];
    char nationality[1024];
    char position[1024];
    int age;
    int appearances;
    Stats playerStats;
    struct Player *next;
} Player;

typedef struct Club
{
    char club[1024];
    struct Player *athlete_head;
    struct Club *next;
} Club;

// function initializer

Club *newClubNode(void)
{
    Club *newClub = NULL;
    newClub = (Club *)malloc(sizeof(Club));

    strcpy(newClub->club, "");
    /*
    newClub->athlete.age = 0;
    strcpy(newClub->athlete->, "");
    strcpy(newClub->athlete.nationality, "");
    strcpy(newClub->athlete.position, "");
    newClub->athlete.playerStats.assists = 0;
    newClub->athlete.playerStats.goals = 0;
    newClub->athlete.appearances = 0;*/
    newClub->athlete_head = NULL;
    newClub->next = NULL;
    //newClub->athlete.next = NULL;
    return newClub;
}

Player *newPlayerNode(void)
{
    Player *newPlayer = NULL;
    newPlayer = (Player *)malloc(sizeof(Player));

    newPlayer->age = 0;
    newPlayer->appearances = 0;
    strcpy(newPlayer->name, "");
    strcpy(newPlayer->nationality, "");
    strcpy(newPlayer->position, "");
    newPlayer->playerStats.goals = 0;
    newPlayer->playerStats.assists = 0;
    newPlayer->next = NULL;

    return newPlayer;
}


Player *insertPlayerAtTail(Club *head, Player *new_player, char clubName[1024])
{
    Club *p = NULL;
    p = head;

    while (p != NULL)
    {
        if (strcmp(p->club, clubName) == 0)
        {
            if (p->athlete_head == NULL)
            {
                p->athlete_head = new_player;
                return new_player;
            }
            else
            {
                new_player->next = p->athlete_head;
                return new_player;
            }
        }
        p = p->next;
    }

    return NULL; //clubname not found in database

}

// inserting new node at head -> returns pointer to new head

Club *insertClubAtHead(Club *head, Club *new_node)
{
    new_node->next = head;
    return new_node;
}

// complexity of O(2)

Club *insertClubAfter(Club *head, Club *new_node, char clubToFind[1024])
{
    Club *p = NULL;
    p = head;

    if (head == NULL)
    {
        printf("No Clubs in list\n");
    }

    while (p != NULL)
    {
        if (strcmp(p->club, clubToFind) == 0)
        {
            new_node->next = p->next;
            p->next = new_node;
            break;
        }
        p = p->next;
    }
    return head;
}

Club *insertClubBefore(Club *head, Club *new_node, char clubToFind[1024])
{
    Club *p = NULL;
    p = head;

    if (head == NULL)
    {
        printf("No Clubs in list\n");
    }

    if (strcmp(p->club, clubToFind) == 0)
    {
        return insertClubAtHead(head, new_node);
    }

    while (p->next != NULL)
    {
        if (strcmp(p->next->club, clubToFind) == 0)
        {
            new_node = p->next;
            p->next = new_node;
            break;
        }
    }
    return head;
}

Club *insertClubAtTail(Club *head, Club *new_node)
{
    Club *p = NULL;

    if (head == NULL)
    {
        return insertClubAtHead(head, new_node);
    }

    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = new_node;

    return head;
}

void printPlayers(Club *head, char clubName[1024])
{
    Club *p = NULL;
    p = head;
    Player *q = NULL;

    while (p != NULL)
    {
        if (strcmp(p->club, clubName) == 0)
        {
            q = p->athlete_head;
            printf("%s\n", clubName);
            while (q != NULL)
            {
                printf("****************************\n");
                printf("Player: %s", q->name);
                printf("Country: %s", q->nationality);
                printf("Age: %d\n", q->age);
                printf("Position: %s", q->position);
                printf("Appearances: %d\n", q->appearances);
                printf("Goals: %d\n", q->playerStats.goals);
                printf("Assists: %d\n", q->playerStats.assists);
                printf("****************************\n");
                q = q->next;
            }
            break;
        }
        p = p->next;
    }
    
}

void printPlayerBySearch(Club *head, char playerName[1024]);


Player *removePlayer(Club *head, char player_name[1024])
{
    Club *p = NULL;
    p = head;
    Player *q = NULL;
    Player *temp = NULL;

    while (p != NULL)
    {
        q = p->athlete_head;

        if (strcmp(p->athlete_head->name, player_name) == 0)
        {
            temp = q->next;
            free(q);
            p->athlete_head = temp;
            return p->athlete_head;
        }

        while (q->next != NULL)
        {
            if (strcmp(q->next->name, player_name) == 0)
            {
                temp = q->next->next;
                free(q->next);
                q->next = temp;
                return p->athlete_head;
            }
            q = q->next;
        }

        p = p->next;
    }
    return head->athlete_head;
}

void cleanUp(Club *head)
{
    Club *p = NULL;
    Club *q = NULL;
    Player *r = NULL;
    Player *s = NULL;
    p = head;

    while (p != NULL)
    {
        r = p->athlete_head;
        while (r != NULL)
        {
            s = r->next;
            free(r);
            r = s;
        }
        q = p->next;
        free(p);
        p = q;
    }
}

int main()
{
    Player *player_head = NULL;
    Player *new_Player = NULL;
    Club *head = NULL;
    Club *new_Club = NULL;
    char team[1024];
    char player[1024];
    char nationality[1024];
    char position[1024];
    int age;
    int appearances;
    int goals;
    int assists;
    int choice = 0;

    while (choice != 10)
    {
        printf("(1) - Insert New Club\n");
        printf("(2) - Insert New Player\n");
        printf("(3) - Print Specific Club's Players\n");
        printf("(4) - Remove Player from List\n");

        printf("(10) - Delete Lists and Exit System\n");
        scanf("%d", &choice);
        getchar();

        if (choice == 1)
        {
            new_Club = newClubNode();
            printf("Please enter name of club\n");
            fgets(team, 1024, stdin);
            strcpy(new_Club->club, team);
            head = insertClubAtHead(head, new_Club);
        }
        else if (choice == 2)
        {
            printf("Please enter team player plays for\n");
            fgets(team, 1024, stdin);
            new_Player = newPlayerNode();
            printf("Please enter name of player\n");
            fgets(player, 1024, stdin);
            strcpy(new_Player->name, player);
            printf("Player's Nationality\n");
            fgets(nationality, 1024, stdin);
            strcpy(new_Player->nationality, nationality);
            printf("Player's Age\n");
            scanf("%d", &age);
            getchar();
            new_Player->age = age;
            printf("Player's Appearances\n");
            scanf("%d", &appearances);
            getchar();
            new_Player->appearances = appearances;
            printf("Player Position\n");
            fgets(position, 1024, stdin);
            strcpy(new_Player->position, position);
            printf("Number of Goals\n");
            scanf("%d", &goals);
            getchar();
            new_Player->playerStats.goals = goals;
            printf("Number of Assists\n");
            scanf("%d", &assists);
            getchar();
            new_Player->playerStats.assists = assists;

            head->athlete_head = insertPlayerAtTail(head, new_Player, team);

        }
        else if (choice == 3)
        {
            printf("Which Club would you like to print?\n\n");
            fgets(team, 1024, stdin);
            printPlayers(head, team);
        }
        else if (choice == 4)
        {
            printf("Which player would you like to remove?\n");
            fgets(player, 1024, stdin);
            head->athlete_head = removePlayer(head, player);
        }

        else if (choice == 6)
        {
            cleanUp(head);
        }


    }


    return 0;
}

