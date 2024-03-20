#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

class LcgGenerator {
private:
    uint16_t mA;
    uint16_t mC;
    uint16_t mCurrentX;
    uint16_t mM;
public:
    LcgGenerator(uint16_t A, uint16_t C, uint16_t CurrentX, uint16_t M) {
        mA = A;
        mC = C;
        mCurrentX = CurrentX;
        mM = M;
    }

    uint16_t next() {
        mCurrentX = (mA * mCurrentX + mC) % mM;
        return mCurrentX;
    }
};

class Card {
private:
    string mSuite;
    uint16_t mValue;
public:
    Card(string const &Suite, uint16_t const &Value) {
        mSuite = Suite;
        mValue = Value;
    }

    Card() {
        mSuite = "\0";
        mValue = 0;
    }

    bool operator==(const Card &c) const {
        if (mSuite == c.mSuite && mValue == c.mValue)
            return true;
        else return false;
    }

    string toString() const {
        return to_string(mValue) + ',' + mSuite;
    }

    bool isFake() const {
        if (mSuite != "rosu" && mSuite != "negru" && mSuite != "romb" && mSuite != "trefla" || mValue < 2 ||
            mValue > 14)
            return true;
        else return false;
    }

    uint16_t getBlackjackValue() const {
        if (mValue <= 10)
            return mValue;
        else
            return 10;
    }

};

class CardPack {
private:
    vector<Card> mCards;
    uint16_t mCurrentIndex;
public:
    CardPack(bool empty = true) {
        if (empty == false) {
            for (int i = 0; i < 9; i++)
                mCards.push_back(Card("rosu", i + 2));
            for (int i = 9; i < 12; i++)
                mCards.push_back(Card("rosu", i + 3));
            for (int i = 12; i < 21; i++)
                mCards.push_back(Card("negru", i - 10));
            for (int i = 21; i < 24; i++)
                mCards.push_back(Card("negru", i - 9));
            for (int i = 24; i < 33; i++)
                mCards.push_back(Card("romb", i - 22));
            for (int i = 33; i < 36; i++)
                mCards.push_back(Card("romb", i - 21));
            for (int i = 36; i < 45; i++)
                mCards.push_back(Card("trefla", i - 34));
            for (int i = 45; i < 48; i++)
                mCards.push_back(Card("trefla", i - 33));
        }
        mCurrentIndex = 0;
    }

    bool goodForBackjack() const {
        int ok = 0;
        for (int i = 0; i < mCards.size(); i++) {
            if (mCards[i].isFake()) {
                ok = 1; //Pachetul este masluit
            }
        }
        if (ok == 0) return true;
        else return false;
    }

    bool ok() const {
        int ok = 0;
        for (int i = 0; i < mCards.size(); i++) {
            if (mCards[i].isFake()) {
                ok = 1; //Pachetul este masluit
            }
        }
        if (mCards.size() != 52) ok = 1;
        //conditie daca toate cartile sunt diferite:
        for (int i = 0; i < mCards.size() - 1; i++) {
            for (int j = i + 1; j < mCards.size(); j++) {
                if (mCards[i] == mCards[j]) {
                    ok = 1;
                }
            }
        }
        if (ok == 0) return true;
        else return false;
    }

    void addCard(const Card &c) {
        mCards.push_back(c);
    }


    void shuffle(uint16_t a1, uint16_t c1, uint16_t x01, uint16_t a2, uint16_t c2, uint16_t x02) {
        LcgGenerator L1(a1, c1, x01, mCards.size());
        LcgGenerator L2(a2, c2, x02, mCards.size());
        for (int i = 0; i < 50; i++) {
            int x1 = L1.next();
            int x2 = L2.next();
            swap(mCards[x1], mCards[x2]);
        }
        mCurrentIndex = 0;
    }

    void printPack() const {
        for (int i = 0; i < mCards.size(); i++) {
            cout << mCards[i].toString() << endl;
        }
    }

    Card nextCard() {
        Card aux = mCards[mCurrentIndex];
        mCurrentIndex++;
        return aux;
    }
};

class Player {
public:
    string mName = "Dealer";
    uint16_t mMoney = 0;
    uint16_t mPoints = 0;

    Player(string Name, uint16_t Money) {
        mName = Name;
        mMoney = Money;
        mPoints = 0;
    }

    string toString() const {
        return mName + ':' + to_string(mMoney);
    }

    void pick(const Card &c) {
        mPoints += c.getBlackjackValue();
    }

    void play(CardPack &c) {
        while (mPoints < 17) {
            pick(c.nextCard());
        }
    }

    void newRound() {
        mPoints = 0;
    }

    bool lostRound() const {
        if (mPoints > 21)
            return true;
        else return false;
    }

    uint16_t getPoints() const {
        return mPoints;
    }

    void operator--() {
        mMoney = mMoney - 10;
    }

    void operator++() {
        mMoney += 10;
    }

    bool lostGame() const {
        if (mMoney < 10) {
            return true;
        } else return false;
    }
};

int main() {

    string comanda;
    cin >> comanda;
    CardPack pachet(true);
    uint16_t nr_carte;
    string stema_carte;
    uint16_t a1, c1, x01;
    uint16_t a2, c2, x02;
    if (comanda == "check_cards") {
        while (cin >> nr_carte) {
            getchar();
            cin >> stema_carte;
            pachet.addCard(Card(stema_carte, nr_carte));
        }
        if (pachet.ok()) {
            cout << "Pachet OK" << endl;
        } else if (pachet.goodForBackjack()) {
            cout << "Pregatit pentru Blackjack" << endl;
        } else cout << "Pachet masluit" << endl;
    } else if (comanda == "shuffle_cards") {
        cin >> a1 >> c1 >> x01;
        cin >> a2 >> c2 >> x02;
        while (cin >> nr_carte) {
            getchar();
            cin >> stema_carte;
            pachet.addCard(Card(stema_carte, nr_carte));
        }
        pachet.shuffle(a1, c1, x01, a2, c2, x02);
        pachet.printPack();
    } else if (comanda == "play_game") {
        int nr_jucatori;
        vector<Player *> jucatori;
        Player Dealer("Dealer", 0);
        string nume_jucator;
        uint16_t suma_bani;
        cin >> nr_jucatori;
        for (int i = 0; i < nr_jucatori; i++) {
            cin >> nume_jucator >> suma_bani;
            jucatori.push_back(new Player(nume_jucator, suma_bani));
        }
        CardPack pachet1(false);
        while (cin >> a1 >> c1 >> x01 >> a2 >> c2 >> x02) {
            pachet1.shuffle(a1, c1, x01, a2, c2, x02);
            for (int i = 0; i < jucatori.size(); i++) {
                jucatori[i]->pick(pachet1.nextCard());
                jucatori[i]->pick(pachet1.nextCard());
            }
            Dealer.pick(pachet1.nextCard());
            Dealer.pick(pachet1.nextCard());

            for (int i = 0; i < jucatori.size(); i++) {
                jucatori[i]->play(pachet1);
            }
            Dealer.play(pachet1);
            for(int i=0;i<jucatori.size();i++){
                if (jucatori[i]->lostRound()) {
                    jucatori[i]->operator--();
                }
                if (Dealer.lostRound()) {
                    jucatori[i]->operator++();
                    if(jucatori[i]->lostRound()){
                        jucatori[i]->operator--();
                    }
                } else if (!(jucatori[i]->lostRound()) && Dealer.mPoints > jucatori[i]->mPoints) {
                    jucatori[i]->operator--();
                } else if (!(jucatori[i]->lostRound()) && Dealer.mPoints < jucatori[i]->mPoints) {
                    jucatori[i]->operator++();
                }
                if(!jucatori[i]->lostGame()){
                    jucatori[i]->newRound();
                } else {
                    vector<Player*>::iterator it=jucatori.begin()+i;
                    jucatori.erase(it);
                    i--;
                }
            }
            Dealer.newRound();
        }
        for (int i = 0; i < jucatori.size(); i++) {
            if (jucatori[i]->lostGame() == false) {
                cout << jucatori[i]->mName << ": " << jucatori[i]->mMoney << endl;
            }
        }
        }
    return 0;
}