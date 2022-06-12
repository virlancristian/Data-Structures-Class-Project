##REZOLVARE TEMA 1 - LAN PARTY BY VÎRLAN CRISTIAN-ALEXANDRU
 
##CITIREA DATELOR DE INTRARE
Rularea programului începe in main.c unde citesc din argv[1] (fișierul c.in) cerințele pentru testul respectiv într-un vector de 5 elemente întregi, unde
tasks[i-1] = cerinta numărul i, unde i = {1,2,3,4,5}
 
Informațiile din fișierul d.in sunt citite prin intermediul funcției read.
 
Funția read primeste ca doi parametri numele fișierului din care se citesc echipele și numărul de echipe reținut prin referință, deoarece pe parcursul programului
se vor face modificări la numărul de echipe. Pentru fiecare echipă care este citită, numele echipei, numărul de persoane al echipei, și datele despre jucătorii respectivi
(nume, prenume, puncte) sunt reținute în niște variabile auxiliare cu care creez un nod nou în lista de echipe cu ajutorul funcției createTeam.
OBS:1)Instrucțiunea teamName[strlen(teamName)-1] = '\0' este folosită pentru a elimina caracterul newline ( \n ) care este citit întrucât poate cauza probleme în afișarea
echipelor în fișierul de output(de exemplu afișare cu spațiu în jos între echipe)
    2)Al doilea fgets din for-ul dedicat pentru citirea datelor fiecărei echipe este pentru a parcurge spațiul gol dintre datele a doua echipe aflat în fișierul d.in
 
##REZOLVARE CERINȚA 1
Pentru rezolvarea cerinței 1 verific daca tasks[0] este egal cu 1(însemnând că cerința este cerută pentru testul respectiv) și dacă este îndeplinită condiția pur și simplu
parcurg lista cu echipe și afisez în fișierul de output pe câte o linie noua numele echipei respective, prin intermediul funcției firstTaskPrint.
 
##REZOLVARE CERINȚA 2
Pentru rezolvarea cerinței 2 verific daca tasks[1] este egal cu 1 și dacă este îndeplinită condiția apelez funcția secondTask.
 
În funcția secondTask mai întâi este aflată cea mai apropriată putere a lui 2 la stânga de numărul de echipe prin intermediul funției getTwoPowered (OBS: deoarece 
este cerută cea mai apropriată putere a lui 2 la stanga în funcția getTwoPowered variabila este împărțită la 2 deoarece dupa sfârșitul while-ului s-a ajuns la o putere
a lui 2 mai mare decât numărul de echipe, iar while-ul se repetă cât timp puterea lui 2 este mai mică sau egală în cazul în care numărul de echipe este o putere a lui 2).
Apoi, cât timp numărul de echipe este mai mare ca puterea lui 2 parcurg lista de echipe și aflu echipa cu numărul cel mai mic de puncte prin intermediul funcției 
findMinPoints și elimin echipa respectivă din listă prin intermediul funcției removeTeam și scad numărul de echipe cu 1. În final, returnez adresa primei echipe ca 
modificările listei să fie aplicate listei de echipe din main.c.
OBS:În funcția de aflare a echipei cu cele mai puține puncte, pentru aflarea punctajului minim și pentru calcularea punctajului echipelor se folosesc variabile de tip
float în cazul în care sunt mai multe echipe cu punctaj minim, caz în care echipa cu punctaj minim este cea cu zecimale mai mici.
În final, in main.c afișez lista de echipe modificată în fișierul de output cu funcția de afișare folosită la prima cerință.
 
##REZOLVARE CERINȚA 3
Pentru rezolvarea cerinței 3 verific daca tasks[2] este egal cu 1 și daca este îndeplinită condiția, deschid fișierul de output și apelez funcția thirdTask.
 
În funcția thirdTask mai întâi afișez în fișierul de output echipele participante la rundele de eliminări și adaug echipele într-o coadă.
Apoi, încep rundele de eliminare astfel: afișez în fișierul de output numărul rundei, apoi parcurg coada din 2 în 2,iar la fiecare pas iau datele despre cele două echipe
aflate la începutul cozii în 2 variabile auxilare team1 și team2(de tip Team)(OBS:când echipele sunt luate din coada pozițiile ocupate de ele sunt eliberate din memorie)
, afișez pe o linie noua numele celor două echipe din meci, calculez echipele celor două 
echipe, și echipa cu punctaj mai mare este băgată în stiva de câștigători, iar cealaltă în stiva de pierzători. După ce-am parcurs întreaga coadă, incrementez punctajul
echipelor câștigătoare prin parcurgerea stivei de câștigori și pentru fiecare echipă incrementez cu 1 punctajul fiecărui jucător în parte, afișez câștigătorii rundei
respective, adaug stiva de câștigători în coada și eliberez stivele pentru runda următoare, apoi împart numărul de echipe la 2(din moment ce fiecare meci are câte 2 
echipe cu un câștigător și un pierzător, după o rundă numărul de echipe rămase se înjumătățește, și nu e nevoie de luat în considerare cazul în care este un număr
impar de echipe deoarece nu ar fi putut avea loc eliminările cu un număr impar de echipe.). La finalul meciurilor din fiecare rundă este verificat dacă numărul de
echipe este 16, și dacă este, înseamnă că s-a ajuns la 8 echipe câștigătoare, astfel că este salvată o copie a celor 8 echipe câștigătoare într-o listă de echipe
de tip Team. Procesul de desfășurare al rundelor de eliminare se repetă până când se ajunge la o echipă rămasă. În final, funcția returneaza adresa primei echipe
din lista celor 8 echipe din topul clasamentului, pentru a fi salvate informațiile în cazul în care sunt cerute cerințele de creare a arborelui binar de căutare/
echilibrat de tip AVL cu cele 8 echipe.
OBS:La finalul fiecărei runde se verifică daca numărul de echipe este mai mare ca 1, pentru a afișa în fișier o linie nouă, deoarece fără această condiție s-ar fi
afișat o linie nouă în fișier când eliminările s-ar fi terminat, rezultând ca checker-ul să nu găsească fișierul de output și fișierul de expected output identice.
 
##REZOLVARE CERINTA 4
Pentru rezolvarea cerinței 3 în main este verificat dacă tasks[3] este egal cu 1 și dacă este îndeplinită condiția, apelez funcția de creare a arborelui binar de căutare
cu ajutorul listei care conține cele 8 echipe din topul clasamentului. În funcție este parcursă lista și pentru fiecare nod din listă se calculează punctajul echipei
și se crează un nod nou în arborele de căutare care este plasat în surbarborele stâng sau drept al arborelui de căutare în funcție de punctaj, sau după ordinea 
alfabetică a numelui echipei în cazul în care se găsește o echipă în arbore cu punctaj identic. Pentru a afișa clasamentul în ordine descrescătoare al punctajului
se face o parcurgere în ordinea dreapta-rădăcină-stânga a arborelui, datorită proprietății arborelui binar de căutare de a păstra valori mai mici decât rădăcina în arborele
drept și mai mari decât rădăcina în subarborele drept, precum și proprietatea că maximul se găsește pe cea mai din dreapta frunză a arborelui, respectiv cea mai din stânga
pentru minim.
În  final, arborele este parcurs din nou pentru a crea o listă sortată a clasamentului în cazul în care este cerută a 5-a cerință
 
##REZOLVARE CERINTA 5
Pentru rezolvarea cerinței 3 în main este verificat dacă tasks[4] este egal cu 1 și dacă este îndeplinită condiția, apelez funcția de creare a arborelui echilibrat
de tip AVL cu ajutorul listei sortate. Deoarece nu este cerută afișarea punctajelor echipelor de pe nivelul 2 al arborelui, putem manipula punctajele astfel încât
să nu mai existe echipe cu punctaje egale, care ar putea modifica altfel decât este cerut arborele, dar să se păstreze aceeași ordine a echipelor. Astfel, lista este parcursă
de la cap la coadă și pentru fiecare nod în parte verific dacă nodurile care urmează după el au punctaj identic, și în caz pozitiv, scad punctajul echipei găsite cu 
un factor de decrementare, care la început e 0.01 și este mărit cu 0.01 de fiecare dată când este găsită o echipă cu punctaj identic. Apoi, echipa este băgată în
arbore, plasat în stânga/dreapta în funcție de punctaj, apoi arborele se reechilibreaza(daca este cazul). În final, arborele este parcurs din nou în ordinea
dreapta-rădăcină-stânga pentru a afișa echipele în modul așteptat, doar că se verifică dacă distanța de la rădăcină la nodul respectiv este egal cu 2, pentru a afișa
doar echipele care se găsesc pe nivelul 2 al arborelui. Inițial, funcția de afișare este apelată cu înalțimea = 0 deoarece se pornește de la rădăcină, și de fiecare
dată când funcția se duce un nod un jos, incrementez cu 1 înălțimea pentru a obține nivelul pe care se afla nodurile.
 
##FINAL
În finalul programului se verifică dacă fișierul de output este dechis(deoarece dacă închidem pur și simplu fișierul programul dă eroare) și îl închidem în caz 
afirmativ(OBS:fișierul de output care a fost deschis la cerința 3 este închis abia acum pentru a evita overwrite-ul conținutului din fișier în cazul în care sunt mai 
multe cerințe cerute dintre 3,4 și 5) și se eliberează lista cu echipele, topul celor 8 echipe(sortat și nesortat), arborele de căutare și cel echilibrat din memorie
prin funcția freeAll( care pentru toate tipurile date în afară de lista inițială se verifică dacă-s nule sau nu pentru a evita erori de memorie).