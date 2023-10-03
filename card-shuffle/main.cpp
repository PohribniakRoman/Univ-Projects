#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

struct ICard{
    int value;
    int suit;
};

class Card {
    ICard card;
public:
    Card(int s, int v) : card(s,v) {}
    auto operator <=> (const Card& other) const = delete;
    bool operator >= (const Card& other) const {
        return  this->card.value >= other.card.value;
    }
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

bool sortPiles(int a,int b){
    return  a>=b;
}

typedef  std::map<int, int> Quantity;

void printOccurrence (std::pair<int,int> occ){
    std::cout<<"A pile with a quantity: "<<occ.first<<" | "<<occ.second<<" times\n";
}

class Analytics{
private:
    Quantity pile_quantity;
public:
    explicit Analytics(std::vector<int> data){
        for (auto &pile : data) {
            if(isInOccurrence(pile)){
                pile_quantity.at(pile)++;
            }else{
                pile_quantity.insert(Quantity::value_type(pile, 1));
            }
        }
    };
    bool isInOccurrence(int value){
        for (auto &i: pile_quantity){
            if (i.first == value) { return true; }
        }
        return false;
    }

    void printAnalytics(){
        std::for_each(pile_quantity.begin(), pile_quantity.end(), printOccurrence);
    }
};


int main() {
    int num_suits = -1, card_amount = -1;
    std::cout << "Enter number of suits: ";
    std::cin >> num_suits;
    std::cout << "Enter number of cards to deal: ";
    std::cin >> card_amount;

    if (num_suits < 0 || card_amount < 0){
        throw  std::invalid_argument( "Received negative value" );
    }
        Deck deck(num_suits);
        std::vector<int> piles_lengths;
        int count = -1;
        Card previous = deck();
        int current_pile_length = 1;

        while (++count < card_amount - 1) {
            Card current = deck();
            if (current >= previous) {
                ++current_pile_length;
            } else {
                piles_lengths.push_back(current_pile_length);
                current_pile_length = 1;
            }
            previous = current;
        }

        if (current_pile_length > 0) {
            piles_lengths.push_back(current_pile_length);
        }

        std::sort(piles_lengths.begin(), piles_lengths.end(), sortPiles);

        if(piles_lengths.size() % 2 == 0){
            std::cout<<"\nPile length medians:\n\tRight: " << piles_lengths[piles_lengths.size() / 2 -1] << "\n\tLeft: " << piles_lengths[piles_lengths.size() / 2 -1]<< "\n\n";
        }else{
            std::cout<<"\nPile length median: " << piles_lengths[piles_lengths.size() / 2]<< "\n\n";
        }

        std::cout << "Avg cards in pile: " << card_amount / piles_lengths.size()<< "\n\n";

        Analytics newAnalytics(piles_lengths);
        newAnalytics.printAnalytics();
    return 0;
}