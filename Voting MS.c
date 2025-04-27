#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 10
#define MAX_CANDIDATES 5
#define MAX_NAME_LEN 50
#define PASSWORD "admin123"

typedef struct {
    char name[MAX_NAME_LEN];
    int votes;
} Candidate;

Candidate candidates[MAX_CANDIDATES];
int candidate_count = 0;

void login() {
    char pass[20];
    printf("Enter admin password to login: ");
    scanf("%s", pass);

    if (strcmp(pass, PASSWORD) != 0) {
        printf("Incorrect password. Exiting...\n");
        exit(0);
    }

    printf("Login successful.\n\n");
}

void registerCandidate() {
    if (candidate_count >= MAX_CANDIDATES) {
        printf("Candidate limit reached!\n");
        return;
    }

    printf("Enter candidate name: ");
    scanf(" %[^\n]s", candidates[candidate_count].name); // reads full name with spaces
    candidates[candidate_count].votes = 0;
    candidate_count++;
    printf("Candidate registered successfully.\n");
}

void castVote() {
    if (candidate_count == 0) {
        printf("No candidates registered.\n");
        return;
    }

    printf("\nCandidates:\n");
    for (int i = 0; i < candidate_count; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }

    int choice;
    printf("Enter your vote (candidate number): ");
    scanf("%d", &choice);

    if (choice < 1 || choice > candidate_count) {
        printf("Invalid choice.\n");
    } else {
        candidates[choice - 1].votes++;
        printf("Vote casted successfully.\n");
    }
}

void displayResults() {
    printf("\nElection Results:\n");
    for (int i = 0; i < candidate_count; i++) {
        printf("%s: %d vote(s)\n", candidates[i].name, candidates[i].votes);
    }

    // Find winner
    int maxVotes = -1, winnerIndex = -1;
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            winnerIndex = i;
        }
    }

    if (maxVotes > 0) {
        printf("Winner: %s with %d vote(s)\n", candidates[winnerIndex].name, maxVotes);
    } else {
        printf("No votes casted yet.\n");
    }
}

int main() {
    int choice;

    printf("=== Voting Management System ===\n");
    login();

    do {
        printf("\nMenu:\n");
        printf("1. Register Candidate\n");
        printf("2. Cast Vote\n");
        printf("3. Display Results\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerCandidate();
                break;
            case 2:
                castVote();
                break;
            case 3:
                displayResults();
                break;
            case 4:
                printf("Exiting system. Goodbye!\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}

