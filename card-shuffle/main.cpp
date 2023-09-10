#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

struct Analytics{
    int value = 0;
    int quantity = 0;
};

struct MedianAnalytics{
    int average = 0;
    int piles_count = 0;
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
    return a.quantity >= b.quantity;
}

int main() {
    int num_suitsToTest, p;
    std::cout << "Enter number of suits: ";
    std::cin >> num_suitsToTest;
    std::cout << "Enter number of cards to deal: ";
    std::cin >> p;

    for(int test_index = 1; test_index <= num_suitsToTest; test_index++) {
        int num_suits = test_index;

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
            bool includes = false;
            for (auto k: uniq) {
                if (k.value == i)includes = true;
            }
            if (!includes) {
                Analytics currentPile(i, 0);
                for (auto j: piles_lengths) {
                    if (i == j)currentPile.quantity++;
                }
                uniq.push_back(currentPile);
            }
        }
        std::sort(uniq.begin(), uniq.end(), compareAnalytics);

        std::vector<MedianAnalytics> Median;
        std::cout << "\n================== " << test_index << " =====================\n";

        for (auto i: uniq) {
            std::cout << "Value - " << i.value << "\tPile Quantity:" << i.quantity << "\t Frequency - " << (double(i.quantity) / double(piles_lengths.size())) * 100 << ";\n";
            const MedianAnalytics currentValue(i.value * i.quantity, i.quantity);
            Median.push_back(currentValue);
        }

        std::cout << "\n";

        if(Median.size() % 2 == 0){
            const size_t first_pile_index = Median.size()/2 - 1;
            const size_t last_pile_index = Median.size()/2;
            std::cout << "First frequency median:" << double(Median[first_pile_index].average) / double(Median[first_pile_index].piles_count) << "\n";
            std::cout << "Last frequency median:" << double(Median[last_pile_index].average) /  double(Median[last_pile_index].piles_count) << "\n";
        }else{
            const size_t pile_index = Median.size()/2;
            std::cout << "Frequency median:" <<double(Median[pile_index].average) /  double(Median[pile_index].piles_count) << "\n";
        }
    }
    return 0;
}