#include <cs50.h>
#include <stdio.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
  if (name_valid(name))
  {
    preferences[voter][rank] = name;
    return true;
  }

  // TODO
  return false;
}

//new
bool name_valid(string name)
{
  for (int i = 0; i < candidate_count; i++)
  {
    if (candidates[i].name == name)
    {
      return true;
    }
  }
  //this triggers only if no candidate was found above with the name
  return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
  for (int i = 0; i < voter_count; i++)
  {
    add_vote(i, 0);
  }

  // TODO
  return;
}

void add_vote(int voter, int rank)
{
  //base case - all candidates have been eliminated
  if (rank == 3)
  {
    return;
  }

  string voter_preference_name = preferences[voter][rank];
  candidate chosen_candidate = get_candidate(voter_preference_name);
  if (chosen_candidate.eliminated)
  {
    add_vote(voter, rank + 1);
    return;
  }
  else
  {
    chosen_candidate.votes += 1;
    return;
  }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
  candidate current_winner = candidates[0];
  bool any_ties_for_first = false;
  for (int i = 1; i < candidate_count; i++)
  {
    candidate new_contender = candidates[i];
    if (new_contender.votes == current_winner.votes)
    {
      any_ties_for_first = true;
    }
    else if (new_contender.votes > current_winner.votes)
    {
      current_winner = new_contender;
      any_ties_for_first = false;
    }
  }
  // TODO
  if (!any_ties_for_first)
  {
    printf("%s", current_winner.name);
    return true;
  }
  return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
  int current_min = candidates[0].votes;
  for (int i = 1; i < candidate_count; i++)
  {
    int ith_candidates_votes = candidates[i].votes;
    if (ith_candidates_votes < current_min)
    {
      current_min = ith_candidates_votes;
    }
  }
  return current_min;
  // TODO
  // return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
  for (int i = 0; i < candidate_count; i++)
  {
    if (candidates[i] > min)
    {
      return false;
    }
  }
  return true;
  // TODO
  // return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
  for (int i = 0; i < candidate_count; i++)
  {
    if (candidates[i].votes == min)
    {
      candidates[i].eliminated = true;
    }
  }
  // TODO
  return;
}
