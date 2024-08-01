#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BACKPACK_SPACE = 275;
const int DNA = 12;
const int NUM_ITEMS = 10;
const int MAX_GENERATIONS = 100;
const float MUTATION_RATE = 0.1;

struct Item {
    int value;
    int space;
};

Item items[NUM_ITEMS] = {
    {6, 1}, {7, 2}, {8, 3}, {9, 4}, {10, 5},
    {11, 6}, {12, 7}, {13, 8}, {14, 9}, {15, 10}
};

struct Individual {
    int genes[NUM_ITEMS];
    int totalValue;
    int totalSpace;
    bool operator<(const Individual& other) const {
        return totalValue > other.totalValue;
    }
};

Individual population[DNA], offspring[DNA];

void initializePopulation();
void calculateFitness(Individual& individual);
void selectBestIndividuals();
void crossover();
void mutate();

int main() {
    srand(time(NULL));
    initializePopulation();

    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        cout << "Generation " << generation + 1 << "\n";
        for (int i = 0; i < DNA; i++) {
            calculateFitness(population[i]);
        }
        selectBestIndividuals();
        crossover();
        mutate();
    }

    return 0;
}

void initializePopulation() {
    cout << "Initialization:\n";
    for (int i = 0; i < DNA; i++) {
        population[i].totalValue = 0;
        population[i].totalSpace = 0;
        for (int j = 0; j < NUM_ITEMS; j++) {
            population[i].genes[j] = rand() % 11;
            cout << population[i].genes[j] << " ";
            if (population[i].genes[j] > 0) {
                population[i].totalSpace += items[j].space * population[i].genes[j];
                population[i].totalValue += items[j].value * population[i].genes[j];
            }
        }
        cout << endl;
        cout << "Total Space: " << population[i].totalSpace << "\n";
        cout << "Total Value: " << population[i].totalValue << "\n";
        if (population[i].totalSpace > BACKPACK_SPACE) {
            cout << "-------------Over capacity, reinitializing--------------\n";
            i--;
        }
    }
}

void calculateFitness(Individual& individual) {
    individual.totalValue = 0;
    individual.totalSpace = 0;
    for (int j = 0; j < NUM_ITEMS; j++) {
        if (individual.genes[j] > 0) {
            individual.totalSpace += items[j].space * individual.genes[j];
            individual.totalValue += items[j].value * individual.genes[j];
        }
    }
    if (individual.totalSpace > BACKPACK_SPACE) {
        individual.totalValue = 1;
    }
}

void selectBestIndividuals() {
    sort(population, population + DNA);
    for (int i = 0; i < DNA / 2; i++) {
        offspring[i] = population[i];
    }
}

void crossover() {
    cout << "Crossover:\n";
    for (int i = DNA / 2; i < DNA; i++) {
        int parent1 = rand() % (DNA / 2);
        int parent2 = rand() % (DNA / 2);
        int crossoverPoint = rand() % NUM_ITEMS;
        for (int j = 0; j < NUM_ITEMS; j++) {
            if (j < crossoverPoint) {
                offspring[i].genes[j] = offspring[parent1].genes[j];
            } else {
                offspring[i].genes[j] = offspring[parent2].genes[j];
            }
        }
        calculateFitness(offspring[i]);
    }
    for (int i = 0; i < DNA; i++) {
        population[i] = offspring[i];
    }
}

void mutate() {
    cout << "Mutation:\n";
    for (int i = 0; i < DNA; i++) {
        for (int j = 0; j < NUM_ITEMS; j++) {
            if ((rand() % 100) / 100.0 < MUTATION_RATE) {
                population[i].genes[j] = rand() % 11;
            }
        }
    }
}