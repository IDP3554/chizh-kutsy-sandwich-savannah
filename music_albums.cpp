#include <iostream>
#include <string>
using namespace std;

enum MusicStyle {
    JAZZ,
    BLUES,
    ROCK,
    POP,
    TECHNO,
    CLASSICAL,
    HIPHOP,
    REGGAE
};

string styleToString(MusicStyle s) {
    switch (s) {
        case JAZZ:      return "Jazz";
        case BLUES:     return "Blues";
        case ROCK:      return "Rock";
        case POP:       return "Pop";
        case TECHNO:    return "Techno";
        case CLASSICAL: return "Classical";
        case HIPHOP:    return "Hip-Hop";
        case REGGAE:    return "Reggae";
        default:        return "Unknown";
    }
}

struct Track {
    string title;
    double duration;
};

const int MAX_TRACKS = 15;

struct Album {
    string title;
    string artist;
    MusicStyle style;
    int year;
    double totalDuration;
    double price;
    int popularity;
    Track tracks[MAX_TRACKS];
    int trackCount;
};

void printAlbum(const Album& a) {
    cout << "======================================\n";
    cout << "Альбом       : " << a.title                   << "\n";
    cout << "Исполнитель  : " << a.artist                  << "\n";
    cout << "Стиль        : " << styleToString(a.style)    << "\n";
    cout << "Год          : " << a.year                    << "\n";
    cout << "Длит. (мин)  : " << a.totalDuration           << "\n";
    cout << "Цена         : " << a.price                   << " $\n";
    cout << "Популярность : " << a.popularity              << "/100\n";
    cout << "Треки:\n";
    for (int i = 0; i < a.trackCount; ++i) {
        cout << "  " << (i + 1) << ". "
             << a.tracks[i].title << " - "
             << a.tracks[i].duration << " мин\n";
    }
    cout << "======================================\n";
}

void printAlbums(const Album arr[], int count, const string& header) {
    cout << "\n--- " << header << " (" << count << " шт.) ---\n";
    if (count == 0) { cout << "(список пуст)\n"; return; }
    for (int i = 0; i < count; ++i) printAlbum(arr[i]);
}

int filterJazzBlues(const Album src[], int srcCount,
                    Album dst[], int dstMax) {
    int n = 0;
    for (int i = 0; i < srcCount && n < dstMax; ++i)
        if (src[i].style == JAZZ || src[i].style == BLUES)
            dst[n++] = src[i];
    return n;
}

void bubbleSortByArtist(Album arr[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - 1 - i; ++j) {
            if (arr[j].artist > arr[j + 1].artist) {
                Album tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void findAndPrintAlbum(const Album arr[], int count,
                       const string& title) {
    cout << "\n--- Поиск: \"" << title << "\" ---\n";
    for (int i = 0; i < count; ++i) {
        if (arr[i].title == title) { printAlbum(arr[i]); return; }
    }
    cout << "Альбом не найден.\n";
}

void printTop5Techno(const Album arr[], int count) {
    Album techno[20];
    int tc = 0;
    for (int i = 0; i < count; ++i)
        if (arr[i].style == TECHNO)
            techno[tc++] = arr[i];

    for (int i = 0; i < tc - 1; ++i)
        for (int j = 0; j < tc - 1 - i; ++j)
            if (techno[j].popularity < techno[j + 1].popularity) {
                Album tmp = techno[j];
                techno[j] = techno[j + 1];
                techno[j+1] = tmp;
            }

    int show = (tc < 5) ? tc : 5;
    cout << "\n Топ-" << show << " Techno альбомов \n";
    for (int i = 0; i < show; ++i)
        cout << (i + 1) << ". \"" << techno[i].title << "\" - "
             << techno[i].artist
             << "  (популярность: " << techno[i].popularity << ")\n";
}

void editAlbum(Album arr[], int count,
               const string& title,
               double newPrice, int newPopularity) {
    for (int i = 0; i < count; ++i) {
        if (arr[i].title == title) {
            arr[i].price = newPrice;
            arr[i].popularity = newPopularity;
            cout << "\n[editAlbum] \"" << title << "\" обновлён: "
                 << "цена=" << newPrice
                 << ", популярность=" << newPopularity << "\n";
            return;
        }
    }
    cout << "\n[editAlbum] Альбом \"" << title << "\" не найден.\n";
}

int filterLongAlbums(const Album src[], int srcCount,
                     Album dst[], int dstMax) {
    int n = 0;
    for (int i = 0; i < srcCount && n < dstMax; ++i)
        if (src[i].totalDuration > 40.0)
            dst[n++] = src[i];
    return n;
}

int main() {

    const int TOTAL = 20;
    Album albums[TOTAL] = {
        //
        {"Kind of Blue", "Miles Davis", JAZZ, 1959, 45.44, 12.99, 98,
         {{"So What",9.22},{"Freddie Freeloader",9.46},{"Blue in Green",5.37},
          {"All Blues",11.33},{"Flamenco Sketches",9.26}}, 5},
        //
        {"The Thrill Is Gone", "B.B. King", BLUES, 1969, 38.10, 9.99, 91,
         {{"The Thrill Is Gone",5.04},{"So Excited",4.22},{"Confessin' the Blues",5.17},
          {"Why I Sing the Blues",6.10},{"Hummingbird",4.09},{"Just a Little Love",3.58},
          {"My Mood",4.50},{"Sweet Sixteen",5.40}}, 8},
        //
        {"Homework", "Daft Punk", TECHNO, 1997, 73.57, 14.99, 95,
         {{"Da Funk",5.28},{"Around the World",7.10},{"Revolution 909",5.48},
          {"Rollin & Scratchin",7.28},{"About to Die",3.51}}, 5},
        //
        {"Discovery", "Daft Punk", TECHNO, 2001, 63.00, 15.99, 97,
         {{"One More Time",5.20},{"Aerodynamic",3.27},{"Digital Love",4.58},
          {"Harder Better Faster",3.45},{"Something About Us",4.08}}, 5},
        //
        {"Thriller", "Michael Jackson", POP, 1982, 42.19, 11.99, 99,
         {{"Wanna Be Startin",6.03},{"Baby Be Mine",4.20},{"The Girl Is Mine",3.42},
          {"Thriller",5.58},{"Beat It",4.18},{"Billie Jean",4.54},
          {"Human Nature",4.06}}, 7},
        //
        {"Rumours", "Fleetwood Mac", ROCK, 1977, 39.43, 10.99, 94,
         {{"Second Hand News",2.43},{"Dreams",4.14},{"Never Going Back Again",2.02},
          {"Don't Stop",3.11},{"Go Your Own Way",3.38},{"The Chain",4.28},
          {"You Make Loving Fun",3.36}}, 7},
        //
        {"Sketches of Spain", "Miles Davis", JAZZ, 1960, 46.35, 13.49, 90,
         {{"Concierto de Aranjuez",16.18},{"Will o' the Wisp",3.36},
          {"The Pan Piper",2.35},{"Saeta",4.55},{"Solea",12.11}}, 5},
        //
        {"Cross Road Blues", "Robert Johnson", BLUES, 1936, 30.05, 7.99, 85,
         {{"Cross Road Blues",2.37},{"Sweet Home Chicago",3.01},
          {"Come On in My Kitchen",3.15},{"Love in Vain",3.23},
          {"Hellhound on My Trail",2.56},{"Me and the Devil Blues",2.53}}, 6},
        //
        {"Random Access Memories", "Daft Punk", TECHNO, 2013, 74.24, 16.99, 96,
         {{"Give Life Back to Music",4.34},{"Get Lucky",6.09},
          {"Instant Crush",5.37},{"Lose Yourself to Dance",5.53},
          {"Fragments of Time",4.36}}, 5},
        //
        {"Legend", "Bob Marley", REGGAE, 1984, 54.41, 10.49, 93,
         {{"Is This Love",4.02},{"No Woman No Cry",7.08},
          {"Could You Be Loved",3.58},{"Three Little Birds",3.00},
          {"Buffalo Soldier",5.25},{"Redemption Song",3.48}}, 6},
        //
        {"Back in Black", "AC/DC", ROCK, 1980, 42.11, 10.99, 97,
         {{"Hells Bells",5.12},{"Shoot to Thrill",5.17},
          {"You Shook Me All Night Long",3.30},{"Back in Black",4.15},
          {"Rock and Roll Ain't Noise Pollution",4.15}}, 5},
        //
        {"Blue", "Joni Mitchell", JAZZ, 1971, 35.47, 9.49, 88,
         {{"All I Want",4.07},{"My Old Man",3.36},{"Little Green",3.28},
          {"Carey",3.00},{"Blue",2.31},{"River",4.00}}, 6},
        //
        {"Texas Flood", "Stevie Ray Vaughan", BLUES, 1983, 42.30, 11.49, 87,
         {{"Love Struck Baby",2.51},{"Pride and Joy",3.39},{"Texas Flood",5.29},
          {"Tell Me",3.43},{"Testify",3.25},{"Rude Mood",3.40},
          {"Mary Had a Little Lamb",3.31}}, 7},
        //
        {"Exciter", "Depeche Mode", TECHNO, 2001, 60.45, 13.99, 80,
         {{"Dream On",4.52},{"Shine",4.14},{"The Sweetest Condition",4.01},
          {"When the Body Speaks",4.35},{"The Dead of Night",4.44}}, 5},
        //
        {"Music for the Masses", "Depeche Mode", TECHNO, 1987, 43.59, 12.99, 86,
         {{"Never Let Me Down Again",4.47},{"The Things You Said",4.07},
          {"Strangelove",4.55},{"Sacred",4.43},{"Little 15",3.37},
          {"Behind the Wheel",5.16}}, 6},
        //
        {"Purple Rain", "Prince", POP, 1984, 43.55, 11.99, 92,
         {{"Let's Go Crazy",4.39},{"Take Me with U",3.54},
          {"When Doves Cry",5.54},{"I Would Die 4 U",2.51},
          {"Purple Rain",8.41}}, 5},
        //
        {"A Love Supreme", "John Coltrane", JAZZ, 1965, 32.57, 10.99, 92,
         {{"Acknowledgement",7.46},{"Resolution",7.24},
          {"Pursuance",10.52},{"Psalm",7.05}}, 4},
        //
        {"In the Ghetto", "B.B. King", BLUES, 1971, 37.24, 8.99, 78,
         {{"Help the Poor",3.41},{"I Got Some Help I Don't Need",3.37},
          {"In the Ghetto",4.04},{"That Evil Child",3.42},
          {"Chains and Things",4.14},{"King's Special",3.05}}, 6},
        //
        {"The Dark Side of the Moon", "Pink Floyd", ROCK, 1973, 42.49, 13.99, 99,
         {{"Speak to Me/Breathe",3.58},{"On the Run",3.30},
          {"Time",7.04},{"Money",6.22},{"Us and Them",7.51},
          {"Brain Damage",3.49}}, 6},
        //
        {"Ambient 1: Music for Airports", "Brian Eno", TECHNO, 1978, 48.47, 11.99, 82,
         {{"1/1",17.22},{"2/1",9.07},{"1/2",12.11},{"2/2",9.09}}, 4}
    };

    // Переписать из исходного массива в другой массив, информацию только о тех альбомах, стиль которых джаз или блюз.
    Album jazzBlues[20];
    int jbCount = filterJazzBlues(albums, TOTAL, jazzBlues, 20);
    
    //Затем новый массив отсортировать по исполнителю по алфавиту. 
    bubbleSortByArtist(jazzBlues, jbCount);

    printAlbums(jazzBlues, jbCount, "Jazz и Blues альбомы");

    // Вывести все данные по конкретному альбому.
    findAndPrintAlbum(albums, TOTAL, "Kind of Blue");

    // Вывести 5 самых популярных техно альбомов.
    printTop5Techno(albums, TOTAL);
    
    // Реализовать функцию изменения альбома.
    editAlbum(albums, TOTAL, "Thriller", 8.99, 100);
    findAndPrintAlbum(albums, TOTAL, "Thriller");

    // В отдельный массив поместить все альбомы длительностью более 40 минут.
    // Реализовать вывод отфильтрованных данных в виде оберточной функции.
    Album longAlbums[20];
    int longCount = filterLongAlbums(albums, TOTAL, longAlbums, 20);
    printAlbums(longAlbums, longCount, "Альбомы длительностью более 40 минут");

    return 0;
}
