/// Hey cunt who is reading this shit code
/// go watch pyrocynical or do something else
/// or you should be prepared for some brain and eye torture
#define M_PI 3.14159265358979323846
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <functional>
#include <string>
#include <bits/stdc++.h>
#include <mutex>
#include <audiere.h>
#include "SortingAlgorithms.h"
#include "SoundLibrary.h"
using namespace sf;
#define Red sf::Color(255, 0, 0)
#define Green sf::Color(0, 255, 0)
#define Blue sf::Color(0, 0, 255)
#define White sf::Color(255, 255, 255)
#define Aqua sf::Color(0, 255, 255)
#define Orange sf::Color(255, 165, 0)
#define Purple sf::Color(148, 0, 211)
#define Magenta sf::Color(255, 0, 255)
#define Yellow sf::Color(255, 255, 0)
#define GreenYellow sf::Color(173,255,47)
#define Pink sf::Color(255,105,180)
sf::Sound sound1, sound2;
sf::SoundBuffer buffer;
sf::Texture n_squared, n_log_n, n_4_3, bogo, lsd, o_n, bead;
sf::Sprite complexity;
///waves
    static double wave_sin(double x){
        return sin(x * 2*M_PI);
    }
    /// sin^3 wave
    static double wave_sin3(double x){
        double s = sin(x * 2*M_PI);
        return s * s * s;
    }

    /// triangle wave
    static double wave_triangle(double x){
        x = fmod(x, 1.0);

        if (x <= 0.25) return 4.0 * x;
        if (x <= 0.75) return 2.0 - 4.0 * x;
        return 4.0 * x - 4.0;
    }
    ///public functions
    short SineWave(double time, double freq, double amp) {
		short result;
		double tpc = 44100 / freq; // ticks per cycle
		double cycles = time / tpc;
		short amplitude = 32767 * amp;
		result = amplitude * wave_sin(cycles);
		return result;
	}
	short SineCubeWave(double time, double freq, double amp) {
		short result;
		double tpc = 44100 / freq; // ticks per cycle
		double cycles = time / tpc;
		short amplitude = 32767 * amp;
		result = amplitude * wave_sin3(cycles);
		return result;
	}
	short TriangleWave(double time, double freq, double amp) {
		short result;
		double tpc = 44100 / freq; // ticks per cycle
		double cycles = time / tpc;
		short amplitude = 32767 * amp;
		result = amplitude * wave_triangle(cycles);
		return result;
	}
enum PAGE {PAGE1, PAGE2, PAGE3};
int n = 100, maxx = n+1, Comps,choice;
float delay = 10;
std::string delayasString = "10";
int v[1000], tmp[1000], Marked[1000];
unsigned long long Swaps;
std::mutex mtx;
std::function<void()> f = std::bind(selectionSort, v);
std::string AlgoNames[] = {"Selection Sort", "Insertion Sort", "Bubble Sort", "Shell Sort", "Shell Sort (Marcin Ciura's Gaps)",
                           "MergeSort", "QuickSort (LR ptrs)", "Radix Sort (LSD Base 4)", "Radix Sort (MSD Base 4)",
                           "Heap Sort", "Cocktail Sort", "Bogo Sort", "Less Bogo Sort", "Pancake Sort", "QuickSort (LL ptrs)",
                           "Comb Sort", "Odd-Even Sort", "Cycle Sort", "Counting Sort", "Hybrid MergeSort", "Bead Sort", "IntroSort",
                           "Binary Insertion Sort"};
const sf::Time OneMilisecondSleep = sf::milliseconds(1);
const sf::Time OneMicrosecondSleep = sf::microseconds(1);
sf::Text AlgoText, NoOfComparisons, NoOfSwaps;
const int w = 1600, h = 768, charSize = 20;
double dw, dh;
bool StartedSorting = false, isSettingDelay = false, isSettingArraySize = false, wasRun = false, lostFocus = false, selectedSort = false, raisedStoppedSorting = false;
PAGE currentPage = PAGE1;
void processDelay(int unicode){
    if(unicode == 8 ) {
            if(delayasString.size()>1){
                delayasString.erase(delayasString.end()-1);
                delay = std::stof(delayasString);
            }
            else{
                delayasString.erase(delayasString.end()-1);
                delayasString.append(1, '0');
                delay = std::stof(delayasString);
            }
    }
    else if(unicode >= '0' && unicode <='9'&& delayasString.size()<6){
        if(delayasString.size()==1 && delayasString[0] == '0'){
            delayasString[0] = (char)unicode;
            delay = std::stof(delayasString);
        }
        else{
            delayasString.append(1, (char)unicode);
            delay = std::stof(delayasString);
        }
    }
    else if(unicode == '.' && delayasString.find('.') == -1){
        delayasString.append(1, (char)unicode);
        delay = std::stof(delayasString);
    }
    ///std::cout<<delay<<std::endl;
}
void doNothing(){
}
void MyReverse(int v[], int n){
    std::sort(v, v+n);
    std::reverse(v, v+n);
}
void MyAlmostSorted(int v[], int n){
    std::sort(v, v+n);
    int pos = rand() % (n-1) ;
    std::swap(v[pos], v[n-1]);
}
void MyShuffle(int v[], int n){
    std::shuffle(v, v + n, std::default_random_engine(time(0)));
}
class Button{
    private:
        sf::Text ButtonText;
        sf::RectangleShape ButtonBox;
        std::string ButtonString;
        bool Idle = true, Hovering = false;
        bool focused = false;
    public:
        ///Constructor
        Button(int x, int y, int w, int h, std::string Text, int Tx, int Ty, sf::Font &DefaultFont){
            ButtonBox.setPosition(x, y);
            ButtonBox.setSize(Vector2f(w, h));
            ButtonBox.setFillColor(sf::Color(0, 0, 0));
            ButtonBox.setOutlineThickness(8);
            ButtonBox.setOutlineColor(Orange);
            ButtonText.setFont(DefaultFont);
            ButtonText.setString(Text);
            ButtonText.setCharacterSize(charSize);
            ButtonText.setFillColor(White);
            ButtonText.setPosition(Tx, Ty);
            ButtonString = Text;
        }
        ///Default Constructor
        Button(){
        }
        void SetAttributes(int x, int y, int w, int h, std::string Text, int Tx, int Ty, sf::Font &DefaultFont){
            ButtonBox.setPosition(x, y);
            ButtonBox.setSize(Vector2f(w, h));
            ButtonBox.setFillColor(sf::Color(0, 0, 0));
            ButtonBox.setOutlineThickness(8);
            ButtonBox.setOutlineColor(Orange);
            ButtonText.setFont(DefaultFont);
            ButtonText.setString(Text);
            ButtonText.setCharacterSize(charSize);
            ButtonText.setFillColor(White);
            ButtonText.setPosition(Tx, Ty);
            ButtonString = Text;
        }
        bool getFocusInfo(){
            return focused;
        }
        void setFocused(bool x){
            focused = x;
        }
        bool Update(Vector2i pos, int id){
            Idle = true;
            Hovering = false;
            if(ButtonBox.getGlobalBounds().contains((double)pos.x * dw, (double)pos.y * dh)){
                Idle = false;
                Hovering = true;
                if(Mouse::isButtonPressed(Mouse::Left) && (!StartedSorting || id == 33)){
                    this->doOnClick();
                    return true;
                }
            }
            return false;
        }
        void SetTxtColor(sf::Color clr){
            ButtonText.setFillColor(clr);
        }
        std::function <void()> doOnClick = std::bind(doNothing);
        void draw(RenderWindow &window, bool drawSpecial){
            window.draw(ButtonBox);
            if(Hovering) this->SetTxtColor(Orange);
            else this->SetTxtColor(White);
            if(drawSpecial) this->SetTxtColor(Aqua);
            window.draw(ButtonText);
        }
        std::string GetString(){
            return ButtonString;
        }
        void ButtonSetString(std::string Text){
            ButtonString = Text;
            ButtonText.setString(Text);
        }
};
void drawArray(RectangleShape &line, RenderWindow &window){
    if(n<=100)line.setOutlineThickness(-std::min((double)(1200.0/n - 1), 1.0));
    else line.setOutlineThickness(0);
    line.setOutlineColor(sf::Color(0, 0, 0));
    for(int i = 0; i<n; i++){
        line.setSize(Vector2f(1200.0/n, 650.0/n * v[i]));
        line.setPosition(1200.0/n*i, h - (650.0/n * v[i]));
        if(Marked[i]==1) line.setFillColor(Red);
        else if(Marked[i]==2) line.setFillColor(Blue);
        else if(Marked[i]==3) line.setFillColor(Aqua);
        else if(Marked[i]==4) line.setFillColor(Purple);
        else if(Marked[i]==5) line.setFillColor(Orange);
        else if(Marked[i]==6) line.setFillColor(Magenta);
        else if(Marked[i]==7) line.setFillColor(Yellow);
        else if(Marked[i]==8) line.setFillColor(GreenYellow);
        else if(Marked[i]==9) line.setFillColor(Pink);
        else if(Marked[i]==10) line.setFillColor(Green);
        else line.setFillColor(White);
        window.draw(line);
    }
}
void SetUpButtons(Button Buttons[], sf::Font &DefaultFont){
    Buttons[0].SetAttributes(1350, 50, 90, 40, "Reverse", 1355, 55, DefaultFont);
    Buttons[0].doOnClick = std::bind(MyReverse, v, n);
    Buttons[1].SetAttributes(1320, 130, 155, 40, "Almost Sorted", 1325, 135, DefaultFont);
    Buttons[1].doOnClick = std::bind(MyAlmostSorted, v, n);
    Buttons[2].SetAttributes(1315, 210, 165, 40, "Random Shuffle", 1320, 215, DefaultFont);
    Buttons[2].doOnClick = std::bind(MyShuffle, v, n);
    Buttons[3].SetAttributes(1315, 290, 170, 40, "Delay: " + delayasString + " ms", 1320, 295, DefaultFont);
    Buttons[3].doOnClick = std::bind(doNothing);
    Buttons[4].SetAttributes(1315, 370, 170, 40, "Array Size: " + std::to_string(n), 1320, 375, DefaultFont);
    Buttons[4].doOnClick = std::bind(doNothing);
    Buttons[5].SetAttributes(1340, 450, 110, 40, "Sorts1 -->", 1345, 455, DefaultFont);
    Buttons[5].doOnClick = std::bind([](){currentPage = PAGE2;Sleep(50);});
    Buttons[6].SetAttributes(1320, 530, 155, 40, "Start Sorting", 1325, 535, DefaultFont);
    Buttons[6].doOnClick = std::bind([](){if(!StartedSorting && selectedSort){StartedSorting = true, Comps = 0, Swaps = 0; std::thread (f).detach(); wasRun = true; raisedStoppedSorting = false;}});
    Buttons[7].SetAttributes(1230, 20, 155, 40, "Selection Sort", 1235, 25, DefaultFont);
    Buttons[7].doOnClick = ([](){f = std::bind(selectionSort, v); AlgoText.setString(AlgoNames[0]); complexity.setTexture(n_squared, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[8].SetAttributes(1230, 100, 155, 40, "Insertion Sort", 1235, 105, DefaultFont);
    Buttons[8].doOnClick = ([](){f = std::bind(insertionSort, v);AlgoText.setString(AlgoNames[1]); complexity.setTexture(n_squared, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[9].SetAttributes(1425, 20, 155, 40, "  Bubble Sort", 1430, 25, DefaultFont);
    Buttons[9].doOnClick = ([](){f = std::bind(BubbleSort, v);AlgoText.setString(AlgoNames[2]); complexity.setTexture(n_squared, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[10].SetAttributes(1425, 100, 155, 40, "  Shell's Sort", 1430, 105, DefaultFont);
    Buttons[10].doOnClick = ([](){f = std::bind(shellSort, v);AlgoText.setString(AlgoNames[3]); complexity.setTexture(n_squared, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[11].SetAttributes(1300, 180, 200, 65, "      Shell's Sort\nMarcin Ciura's Gaps", 1305, 185, DefaultFont);
    Buttons[11].doOnClick = ([](){f = std::bind(shellSort, v);AlgoText.setString(AlgoNames[4]);complexity.setTexture(n_4_3, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[12].SetAttributes(1230, 285, 155, 65, "    Quicksort\n     (LR ptrs)", 1235, 290, DefaultFont);
    Buttons[12].doOnClick = ([](){f = std::bind(QuickSortHoareInit, v);AlgoText.setString(AlgoNames[6]); complexity.setTexture(n_log_n, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[13].SetAttributes(1425, 285, 155, 65, "    Quicksort\n     (LL ptrs)", 1425, 290, DefaultFont);
    Buttons[13].doOnClick = ([](){f = std::bind(QuickSortLomutoInit, v);AlgoText.setString(AlgoNames[14]);complexity.setTexture(n_log_n, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[14].SetAttributes(1425, 390, 155, 40, "    HeapSort", 1430, 395, DefaultFont);
    Buttons[14].doOnClick =([](){f = std::bind(heapSort, v);AlgoText.setString(AlgoNames[9]);complexity.setTexture(n_log_n, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[15].SetAttributes(1230, 390, 155, 40, "   MergeSort", 1235, 395, DefaultFont);
    Buttons[15].doOnClick =([](){f = std::bind(MergeSortInit, v);AlgoText.setString(AlgoNames[5]);complexity.setTexture(n_log_n, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[16].SetAttributes(1230, 470, 155, 65, "   Radix Sort\n   LSD Base 4", 1235, 475, DefaultFont);
    Buttons[16].doOnClick = ([](){f = std::bind(radixsortLSDInit, v);AlgoText.setString(AlgoNames[7]);complexity.setTexture(lsd, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[17].SetAttributes(1425, 470, 155, 65, "   Radix Sort\n   MSD Base 4", 1430, 475, DefaultFont);
    Buttons[17].doOnClick = ([](){f = std::bind(RadixSortMSDInit, v);AlgoText.setString(AlgoNames[8]);complexity.setTexture(lsd, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[18].SetAttributes(1230, 575, 155, 40, "Cocktail Sort", 1235, 580, DefaultFont);
    Buttons[18].doOnClick = ([](){f = std::bind(CocktailSort, v); AlgoText.setString(AlgoNames[10]);complexity.setTexture(n_squared, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[19].SetAttributes(1425, 575, 155, 40, " Comb Sort", 1430, 580, DefaultFont);
    Buttons[19].doOnClick = ([](){f = std::bind(CombSort, v);AlgoText.setString(AlgoNames[15]);complexity.setTexture(n_squared, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[20].SetAttributes(1230, 665, 155, 40, "<--Settings", 1235, 670, DefaultFont);
    Buttons[20].doOnClick = std::bind([](){currentPage = PAGE1;Sleep(50);});
    Buttons[21].SetAttributes(1425, 665, 155, 40, "   Sorts2-->", 1430, 670, DefaultFont);
    Buttons[21].doOnClick = std::bind([](){currentPage = PAGE3;Sleep(50);});
    Buttons[22].SetAttributes(1230, 665, 155, 40, "<-- Sorts1", 1235, 670, DefaultFont);
    Buttons[22].doOnClick = std::bind([](){currentPage = PAGE2;Sleep(50);});
    Buttons[23].SetAttributes(1230, 40, 155, 40, "   Bogo Sort", 1235, 45, DefaultFont);
    Buttons[23].doOnClick = ([](){f = std::bind(BogoSort, v);AlgoText.setString(AlgoNames[11]);complexity.setTexture(bogo, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[24].SetAttributes(1425, 40, 155, 40, "Pancake Sort", 1439, 45, DefaultFont);
    Buttons[24].doOnClick = ([](){f = std::bind(PancakeSort, v);AlgoText.setString(AlgoNames[13]);complexity.setTexture(n_squared, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[25].SetAttributes(1230, 120, 155, 40, "Less Bogo Sort", 1235, 125, DefaultFont);
    Buttons[25].doOnClick = ([](){f = std::bind(LessBogoSort, v); AlgoText.setString(AlgoNames[12]);complexity.setTexture(bogo, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[26].SetAttributes(1425, 120, 155, 40, "Odd-Even Sort", 1430, 125, DefaultFont);
    Buttons[26].doOnClick = ([](){f = std::bind(oddEvenSort, v);AlgoText.setString(AlgoNames[16]);complexity.setTexture(n_squared, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[27].SetAttributes(1230, 200, 155, 40, "Cycle Sort", 1235, 205, DefaultFont);
    Buttons[27].doOnClick = ([](){f = std::bind(CycleSort, v); AlgoText.setString(AlgoNames[17]);complexity.setTexture(n_squared, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[28].SetAttributes(1425, 200, 155, 40, "Counting Sort", 1430, 205, DefaultFont);
    Buttons[28].doOnClick = ([](){f = std::bind(CountingSort, v); AlgoText.setString(AlgoNames[18]);complexity.setTexture(o_n, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[29].SetAttributes(1230, 280, 155, 40, "IntroSort", 1235, 285, DefaultFont);
    Buttons[29].doOnClick = ([](){f = std::bind(introSortInit, v); AlgoText.setString(AlgoNames[21]);complexity.setTexture(n_log_n, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[30].SetAttributes(1425, 280, 155, 40, "Bead Sort", 1430, 285, DefaultFont);
    Buttons[30].doOnClick = ([](){f = std::bind(BeadSort, v); AlgoText.setString(AlgoNames[20]);complexity.setTexture(bead, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[31].SetAttributes(1230, 360, 155, 65, "      Hybrid\n  MergeSort", 1235, 365, DefaultFont);
    Buttons[31].doOnClick = ([](){f = std::bind(HybridMergeSort, v); AlgoText.setString(AlgoNames[19]);complexity.setTexture(n_log_n, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[32].SetAttributes(1425, 360, 155, 65, "      Binary \nInsertion Sort", 1430, 365, DefaultFont);
    Buttons[32].doOnClick = ([](){f = std::bind(BinaryInsertionSort, v); AlgoText.setString(AlgoNames[22]);complexity.setTexture(n_squared, 1); complexity.setPosition(5, 3*charSize + 5);});
    Buttons[33].SetAttributes(1320, 600, 155, 40, "Stop Sorting", 1325, 605, DefaultFont);
    Buttons[33].doOnClick = ([](){raisedStoppedSorting = true;});
}
void DrawButtons(Button Buttons[], RenderWindow &window, int s, int n){
    for(int i = s; i<n; i++) {
            if((i == 3 && isSettingDelay) || (i==4 && isSettingArraySize)) {
                    Buttons[i].draw(window, true);
            }
            else Buttons[i].draw(window, Buttons[i].getFocusInfo());
    }
}
void CallWindow(){
	srand(time(0));

    std::vector <sf::Int16> samples;
    for(int i = 0; i < 441000; i++){
        samples.push_back(TriangleWave(i, 440, 0.3));
    }
    buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);
    sound1.setBuffer(buffer);
    sound2.setBuffer(buffer);
    sf::Image icon;
    icon.loadFromFile("Resources/interfata.png");
    n_squared.loadFromFile("Resources/n patrat.png");
    n_log_n.loadFromFile("Resources/n log n.png");
    lsd.loadFromFile("Resources/lsd.png");
    bogo.loadFromFile("Resources/bogo.png");
    n_4_3.loadFromFile("Resources/4 over 3.png");
    o_n.loadFromFile("Resources/n.png");
    bead.loadFromFile("Resources/bead.png");
    /// Text
    sf::Font DefaultFont;
    if(!DefaultFont.loadFromFile("Resources/comic.ttf")){
        printf("Error opening font file!");
    }
    AlgoText.setFont(DefaultFont);
    NoOfComparisons.setFont(DefaultFont);
    NoOfSwaps.setFont(DefaultFont);
    AlgoText.setCharacterSize(charSize);
    NoOfComparisons.setCharacterSize(charSize);
    NoOfSwaps.setCharacterSize(charSize);
    AlgoText.setFillColor(White);
    NoOfComparisons.setFillColor(White);
    NoOfSwaps.setFillColor(White);
    AlgoText.setPosition(5, 0);
    NoOfComparisons.setPosition(5, charSize);
    NoOfSwaps.setPosition(5, 2*charSize);
    ///Window
    sf::RenderWindow window(VideoMode(w, h), "Sorts");
    window.setActive(false);
    window.setFramerateLimit(60);
    RectangleShape line(Vector2f(0, 0));
    /// Buttons
    Button Buttons[50];
    SetUpButtons(Buttons, DefaultFont);
    for(int i = 0; i<n; i++){
            v[i] = i+1;
    }
    window.setIcon(32, 32, icon.getPixelsPtr());
    while (window.isOpen()){
        SetUpButtons(Buttons, DefaultFont);
        Event e;
        Vector2i pos = Mouse::getPosition(window);
        dw = ((double)w / window.getSize().x);
        dh = ((double)h / window.getSize().y);
        std::cout << dw << " " << dh << std::endl;
        while (window.pollEvent(e)){

            if (e.type == Event::Closed) {
                    window.close();
                    exit(0);
            }
            if(e.type == Event::LostFocus){
                lostFocus = true;
            }
            if(e.type == Event::GainedFocus){
                lostFocus = false;
            }
            if(currentPage == PAGE1){
                if(isSettingDelay && !StartedSorting){
                    if(e.type == Event::TextEntered){
                        processDelay(e.text.unicode);
                    }
                }
                if(isSettingArraySize && !StartedSorting){
                    if(e.type == Event::TextEntered){
                        if(e.text.unicode - '0' <= 9 && e.text.unicode - '0' >= 0 && log10(n)<2){
                            n *= 10;
                            n += e.text.unicode - '0';
                        }
                        else if(e.text.unicode == 8){
                            n/=10;
                        }
                        for(int i = 0; i<n; i++){
                            v[i] = i+1;
                        }
                    }
                }
                for(int i = 0; i < 7; i++){
                    if(Buttons[i].Update(pos, i)){
                        if(i==3) isSettingDelay = true;
                        else isSettingDelay = false;
                        if(i==4) isSettingArraySize = true;
                        else isSettingArraySize = false;
                        Sleep(50);
                    }
                }
                if(Buttons[33].Update(pos, 33)){
                    Sleep(50);
                }
            }
            else if(currentPage == PAGE2){
                for(int i = 7; i < 22; i++){
                    if(Buttons[i].Update(pos, i)){
                        Buttons[i].setFocused(true);
                        if(i < 20) selectedSort = true, raisedStoppedSorting = false;
                        Buttons[20].setFocused(false);
                        Buttons[21].setFocused(false);
                        for(int j = 0; j < 33 && i < 20; j++){
                            if(j!=i) Buttons[j].setFocused(false);
                        }
                        Sleep(50);
                    }
                }
            }
            else if(currentPage == PAGE3){
                for(int i = 22; i<33; i++){
                    if(Buttons[i].Update(pos, i)){
                        Buttons[i].setFocused(true);
                        if(i==22)Buttons[i].setFocused(false);
                        else selectedSort = true, raisedStoppedSorting = false;
                        for(int j = 0; j < 33 && i != 22; j++){
                            if(j!=i) Buttons[j].setFocused(false);
                        }
                        Sleep(50);
                    }
                }
            }
		}
		if(StartedSorting){
            NoOfComparisons.setString((std::string)("Comparisons :" + std::to_string(Comps)));
            NoOfSwaps.setString((std::string)("Swaps : " + std::to_string(Swaps)));
            ///clear
            window.clear();
            ///draw
            if(currentPage == PAGE1){
                    DrawButtons(Buttons, window, 0, 7);
                    DrawButtons(Buttons, window, 33, 34);
            }
            else if(currentPage == PAGE2){
                    DrawButtons(Buttons, window, 7, 22);
            }
            else if(currentPage == PAGE3){
                    DrawButtons(Buttons, window, 22, 33);
            }
            ///std::cout << std::boolalpha << raisedStoppedSorting << std::endl;
            window.draw(AlgoText);
            window.draw(NoOfComparisons);
            window.draw(NoOfSwaps);
            window.draw(complexity);
            drawArray(line, window);
            ///display
            window.display();
		}
		else{
            NoOfComparisons.setString((std::string)("Comparisons :" + std::to_string(Comps)));
            NoOfSwaps.setString((std::string)("Swaps : " + std::to_string(Swaps)));
            ///clear
            window.clear();
            ///draw
            ///
            if(wasRun){
                window.draw(AlgoText);
                window.draw(NoOfComparisons);
                window.draw(NoOfSwaps);
                window.draw(complexity);
            }
            if(currentPage == PAGE1){
                    DrawButtons(Buttons, window, 0, 7);
            }
            else if(currentPage == PAGE2){
                    DrawButtons(Buttons, window, 7, 22);
            }
            else if(currentPage == PAGE3){
                    DrawButtons(Buttons, window, 22, 33);
            }
            drawArray(line, window);
            ///display
            window.display();
		}
	}
}
int main(){
    std::thread (CallWindow).detach();
    while(1) Sleep(1);
}
