#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

//Déclaration des const

const int ASCII_Max = 126;
const int ASCII_Min = 32;

const int MyCode_Max = ASCII_Max - ASCII_Min;
const int MyCode_Min = 0;

//Var

int error(0);
string mode, saveas;

//Fonctions

bool verifExt(string word, string ext)
{
    bool re;
    int word_i = word.size();
    int ext_i = ext.size();
    const int ext_size = ext_i;

    do
    {
        if(word[word_i] == ext[ext_i])
        {
            re = true;
        }
        else
        {
            re = false;
        }
        word_i--;
        ext_i--;
    }
    while(re && ext_i )
}

int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}

int conversion_char_int(char a)
{
    int ASCIIOfChar = a; //convesrion effectuer

    if (ASCIIOfChar >= ASCII_Min && ASCIIOfChar <= ASCII_Max)
    {
        return ASCIIOfChar; //on retourne la valeur ASCII du caractère
    }
    else
    {
        return 0; //on retourn 0 car le caractère n'est pas compris dans la plage de fonctionnement (32 à 126 | (espace) à ~)
    }
}

char conversion_int_char(int a)
{
    const char vide = 0;

    if (a >= ASCII_Min && a <= ASCII_Max)
    {
        char CharOfASCII = a; //convesrion effectuer
        return CharOfASCII; //on retourne le caractère de la valeur ASCII
    }
    else
    {
        return vide; //on retourn "rien" car le code ASCII n'est pas compris dans la plage de fonctionnement (32 à 126 | (espace) à ~)
    }
}

string getKeyOfUser()
{
    string Key;

    cout << "enter the KEY : " << "\n[leave blank for a random key]" << endl;
    getline(cin, Key);

    if (Key != "")
    {
        return Key;
    }
    else
    {
        int Key_ASCII_cara;
        const int NbrCara = rand_a_b(20, 50);
        for (int i(0); i < NbrCara; i++)
        {
            Key_ASCII_cara = rand_a_b(ASCII_Min, ASCII_Max+1);
            Key.push_back(conversion_int_char(Key_ASCII_cara));
        }

        ofstream Key_file("Key.txt");
        if(Key_file)
        {
            Key_file << Key << endl;
        }
        else
        {
            system("pause");
            exit(EXIT_FAILURE);
        }
        Key_file.close();
        return Key;
    }
}

string ajoutTXT(string a)
{
    a.push_back('.');
    a.push_back('t');
    a.push_back('x');
    a.push_back('t');

    return a;
}

vector<int> conversion_str_vectInt(string a)
{
    vector<int> result;
    int tmp;

    int taille(a.size());
    for(int i=0; i < taille; i++)
    {
        tmp = conversion_char_int(a[i]);
        result.push_back(tmp);
    }
    return result;
}

string conversion_vectInt_str(vector<int> tab)
{
    string result("");
    for(unsigned int i(0); i<tab.size(); ++i)
    {
        result.push_back(conversion_int_char(tab[i]));
    }

    return result;
}

int convert_ASCII_MyCode(int a)
{
    return a - ASCII_Min;
}

int convert_MyCode_ASCII(int b)
{
    return b + ASCII_Min;
}

vector<string> Crypto(bool crypt, vector<string> Words, string Key)
{
    int Words_MyCode;
    vector<int> Key_MyCode;
    vector<int> result_ASCII_tmp;
    vector<string> result_sring_final;
    int newChar_MyCode, taille12223;
    int KeyPlace(0);

    //convertion de la clé en tableau de nombre MyCode
    for(unsigned int i(0); i < Key.size(); i++)
    {
        Key_MyCode.push_back(convert_ASCII_MyCode(conversion_char_int(Key[i])));
    }

    //Lecture d'une ligne
    for(unsigned int i(0); i < Words.size(); ++i)
    {
        //lecture d'un caractère
        for(unsigned int ii(0); ii < Words[i].size(); ii++)
        {
            //convertion d'un caractère de la ligne en nombre MyCode
            Words_MyCode = convert_ASCII_MyCode(conversion_char_int(Words[i][ii]));

            //MODE CRYPT -> Addition des caractères
            if (crypt)
            {
                newChar_MyCode = Words_MyCode + Key_MyCode[KeyPlace];

                if (newChar_MyCode > MyCode_Max)
                {
                    newChar_MyCode -= MyCode_Max;
                }
            }

            //MODE DECRYPT -> Soustraction des caractères
            else if (!crypt)
            {
                newChar_MyCode = Words_MyCode - Key_MyCode[KeyPlace];

                if (newChar_MyCode < MyCode_Min)
                {
                    newChar_MyCode += MyCode_Max;
                }
            }
            else
            {
                system("pause");
                exit(EXIT_FAILURE);
            }
            //écriture du caractère crypter / décryper en ASCII
            result_ASCII_tmp.push_back(convert_MyCode_ASCII(newChar_MyCode));

            KeyPlace++;
            KeyPlace = KeyPlace % Key.size();
        }

        //convesrtion de la ligne ASCII en string er écriture dans le tableau final
        result_sring_final.push_back(conversion_vectInt_str(result_ASCII_tmp));

        //ecrasement du tableau temporaire
        taille12223 = result_ASCII_tmp.size();
        for(int i(0); i < taille12223; i++)
        {
            result_ASCII_tmp.pop_back();
        }
    }

    return result_sring_final;
}

void CryptOrDecryptFiles(string FilePath)
{

    //Déclaration des Var
    vector<string> Fichier_processed_tab;
    vector<string> Fichier_processed_tab__verif;
    vector<string> Fichier_not_processed_tab;
    string ligne, cryptKey;
    int displayMode;
    bool dispsayConsol, writeFile, crypt;

    ifstream fichier(FilePath.c_str()); //ouverture du fichier

    if (fichier) //vérification de l'ouverture du fichier
    {
        //séléction du mode ("crypt" ou "decrypt")
        //boucle tant que l'utilisateur n'entre pas soit "crypt" ou "decrypt"
        do
        {
            if(error < 1)
            {
                cout << "crypt or decrypt this file : " << endl; //texte de départ
            }
            else
            {
                cout << "[ERROR] : try again (type crypt or decrypt)" << endl; //texte d'erreur
            }
            cin >> mode; //entrer utilisateur
            error++;
        }
        while(mode != "crypt" && mode != "decrypt" && mode != "c" && mode != "d");
        cin.ignore();
        system("cls");

        if (mode == "crypt" || mode == "c")
        {
            cout << "------------------\nCRYPT MODE\n------------------\n" << endl;
            crypt = true;
        }
        else if (mode == "decrypt" || mode == "d")
        {
            cout << "------------------\nDECRYPT MODE\n------------------\n" << endl;
            crypt = false;
        }
        else
        {
            exit(EXIT_FAILURE); //aucun mode séléctionner = erreur = arret du programme
        }

        //stockae du fichier dans un tableau
        while (getline(fichier, ligne))
        {
            Fichier_not_processed_tab.push_back(ligne); //ajout de la ligne à la fin du tableau de string
        }
        fichier.close(); //fichier lu et enregister dans le tableau -> fermeture du fichier

        system("cls");

        //renseignement de la clé de cryptage / décryptage par l'utilisateur
        cryptKey = getKeyOfUser();

        //CRYPTAGE - DECRYPTAGE
        Fichier_processed_tab = Crypto(crypt, Fichier_not_processed_tab, cryptKey);
        Fichier_processed_tab__verif = Crypto(!crypt, Fichier_processed_tab, cryptKey);
        if (Fichier_not_processed_tab != Fichier_processed_tab__verif)
        {
            cout << "[ERROR] : impossible to crypt / decrypt this file" << endl;
            system("pause");
            exit(EXIT_FAILURE);
        }

        //séléction du mode d'affichage du fichier crypter / décrypter
        system("cls");
        do
        {
            cout << "Choose a display mode :" << endl;
            cout << " - In console and in file (1)" << endl;
            cout << " - Just in console (2)" << endl;
            cout << " - just in file (3)" << endl;
            cin >> displayMode;
        }
        while(displayMode != 1 && displayMode != 2 && displayMode != 3);

        switch(displayMode)
        {
            case 1:
                dispsayConsol = true;
                writeFile = true;
                break;

            case 2:
                dispsayConsol = true;
                writeFile = false;
                break;

            case 3:
                dispsayConsol = false;
                writeFile = true;
                break;

            default:
                exit(EXIT_FAILURE);
                break;
        }

        if (writeFile)
        {
            cout << "Save As :" << endl;
            cin >> saveas;

            saveas = ajoutTXT(saveas);

            //écriture dans le fichier de résultat le text crypter/decrypter
            ofstream fichier(saveas.c_str()); //ouverture du fichier
            if(fichier)  //vérification de l'ouverture du fichier
            {
                //écriture ligne par ligne du fichier crypter / décrypter
                for(unsigned int i(0); i < Fichier_processed_tab.size(); i++)
                {
                    //convesrion tableau ASCII -> Chiane de caractère
                    fichier << Fichier_processed_tab[i] << endl;
                }
            }
            else
            {
                //erreur : impossible de créé ou d'écrire dans le fichier séléctionner -> quitte l'application
                cout << "[ERROR] : impossible to create and/or write \"" << saveas << "\"" << endl;
                system("pause");
                exit(EXIT_FAILURE);
            }
        }

        if (dispsayConsol)
        {
            system("cls");

            for(unsigned int i(0); i < Fichier_processed_tab.size(); ++i)
            {
                //convesrion tableau ASCII -> Chiane de caractère
                cout << Fichier_processed_tab[i] << endl;
            }

            system("pause");
        }
    }
    else
    {
        //erreur : impossible de trouver ou de lire dans le fichier séléctionner -> quitte l'application
        cout << "[ERROR] : impossible to find and/or open \"" << FilePath << "\"" << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    system("title = CRYPTO V1 By Diab24");
    srand(time(NULL)); // initialisation de rand
    if (argc == 2)//méhode de glisser déposer
    {
        CryptOrDecryptFiles(argv[1]);
    }
    else if (argc == 1)
    {
        string word;
        string cryKey;
        vector<string> tab_word;
        vector<string> tab_word_crypt;
        //renseignement du texte par l'utilisateur
        cout << "------------------------------------" << "\nENTER YOUR TEXT\n[type \"STOP\" when your text is finish]" << "\n------------------------------------" << endl;
        do
        {
            getline(cin, word);
            if (word != "STOP")
            {
                tab_word.push_back(word);
            }
        }
        while(word != "STOP");

        cryKey = getKeyOfUser();
        tab_word_crypt = Crypto(true, tab_word, cryKey);
        system("cls");
        cout << "Save As :" << endl;
        cin >> saveas;

        saveas = ajoutTXT(saveas);

        //écriture dans le fichier de résultat le text crypter/decrypter
        ofstream fichier(saveas.c_str()); //ouverture du fichier
        if(fichier)  //vérification de l'ouverture du fichier
        {
            //écriture ligne par ligne du fichier crypter / décrypter
            for(unsigned int i(0); i < tab_word_crypt.size(); i++)
            {
                //convesrion tableau ASCII -> Chiane de caractère
                fichier << tab_word_crypt[i] << endl;
            }
        }
        else
        {
            //erreur : impossible de créé ou d'écrire dans le fichier séléctionner -> quitte l'application
            cout << "[ERROR] : impossible to create and/or write \"" << saveas << "\"" << endl;
            system("pause");
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}
