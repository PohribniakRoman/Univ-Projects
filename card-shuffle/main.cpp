#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

struct Analytics{
    int value = 0;
    int frequency = 0;
};

class Card {
public:
    int suit;
    int value;
    Card(int s, int v) : suit(s), value(v) {}
    auto operator <=> (const Card& other) const = default;
};

class Deck {
    std::vector<Card> cards;
    size_t index;

public:
    explicit Deck(int num_suits) : index(0) {
        for (int s = 0; s < num_suits; s++) {
            for (int v = 1; v <= 13; v++) {
                cards.emplace_back(s, v);
            }
        }
        shuffle();
    }

    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
        index = 0;
    }

    Card operator()() {
        if (index == cards.size()) {
            shuffle();
        }
        return cards[index++];
    }
};

bool compareAnalytics(Analytics a,Analytics b){
    return  a.frequency >= b.frequency;
}

int main() {
    int num_suits, p;
    std::cout << "Enter number of suits: ";
    std::cin >> num_suits;
    std::cout << "Enter number of cards to deal: ";
    std::cin >> p;

    Deck deck(num_suits);
    std::vector<int> piles_lengths;

    int count = 0;
    Card previous = deck();
    int current_pile_length = 1;

    while (count++ < p - 1) {
        Card current = deck();

        if (current.value >= previous.value) {
            current_pile_length++;
        } else {
            piles_lengths.push_back(current_pile_length);
            current_pile_length = 1;
        }

        previous = current;
    }

    if (current_pile_length > 0) {
        piles_lengths.push_back(current_pile_length);
    }

    std::vector<Analytics> uniq;
    for (auto i: piles_lengths) {
        bool includes  = false;
        for (auto k: uniq) {
            if(k.value == i)includes = true;
        }
        if(!includes){
            Analytics currentPile(i,0);
            for (auto j: piles_lengths) {
                if(i == j)currentPile.frequency++;
            }
            uniq.push_back(currentPile);
        }
    }
    std::sort(uniq.begin(),uniq.end(), compareAnalytics);

    for (auto i : uniq) {
        std::cout<<"Value - "<<i.value<<"\tPile Count:"<<i.frequency<<"\tFrequency - "<< (double(i.frequency)/double(piles_lengths.size()))*100<<"%\n";
    }
    return 0;
}