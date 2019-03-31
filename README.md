# Poker-Tournament
Programul presupune realizarea unei aranjari efeciente a jucatorilor la un turneu de poker folosind Structuri de Date si anume liste(generice).

--Acest program simuleaza aranajarea si re-aranjarea jucatorilor la un turneu de poker, la anumite mese, urmand anumite conditii.

1. Sala de joc e reprezentata sub forma unei liste simplu inlantuite fara santinela.
2. O masa de joc este reprezentata sub forma unei liste circulare simplu inlantuite cu santinela.Aceasta are in componenta sa numele mesei (char*), numarul curent de jucatori (int), numarul maxim de jucatori (int) si o lista de elemente de tip jucator.
3.Jucatorul va fi definit printr-o structura ce are un id de identificare(char*) si un numar de maini pe care le mai poate juca la momentul curent(int).
Programul primeste ca argumente la rulare 3 fisiere :
--configuratie.txt - configurarea initiala a meselor si informatii despre jucatori
--evenimente.txt - inlantuirea de evenimente ce avea loc asupra salii de joc
--out.txt - output-ul cerut pentru afișare în urma diferitelor evenimente

--Evenimentele ce pot avea loc asupra salii/meselor/jucatorilor:
1. print - se face afisare salii la momentul curent, format: Nume_masa_1: nume_jucător_1 - număr_mâini_jucător_1; nume_jucător_2 - număr_mâini_jucător_2; .....; nume_jucător_n1 - număr_mâini_jucător_n1.
Nume_masa_2: nume_jucător_1 - număr_mâini_jucător_1; nume_jucător_2 - număr_mâini_jucător_2; .....; nume_jucător_n2 -număr_mâini_jucător_n2.........
Nume_masa_N: nume_jucător_1 - număr_mâini_jucător_1; nume_jucător_2 - număr_mâini_jucător_2; .....; nume_jucător_nN -număr_mâini_jucător_nN. 
Unde n1, n2, .., ni, .. nN - reprezintă numărul de jucători de la masa i , N - reprezinta numărul de mese.
In cazul in care nu exista nicio masa, se va afisa "Sala este inchisa".

2.noroc [nume_masa][nume_jucator][grad_noroc] - eveniment prin care un jucator primeste mai multe sanse de a ramane in joc, numarul de maini(puncte) pe care acesa le poate juca fiind incrementat.

3.noroc [nume_masa][nume_jucator][grad_ghinion] - eveniment opus precendentului (noroc), prin care unui jucator i se scade din numarul de maini(puncte)

4.tura[nume_masa] - eveniment prin care se informeaza ca a avut loc o mana jucata la o anumita masa. Acest lucru implica decrementarea cu 1 a valorii din campul numarului de maini pentru fiecare jucator de la masa respectiva si reordonarea in lista similar unei rotatii in jurul santinelei: al doilea jucator devine primul, al treilea devine al doilea.....

5.tura_completa - evenimnetul are un comportament similar celui precedent (tura), insa modificarea va fi apliata pentru toate mesele al acest moment. 

6.clasament[nume_masa] - prin apelarea acestui eveniment, se va afisa in fisierul de output un clasament al jucatorilor la o anumita masa, descrescator dupa numarul de maini ramase pentru a fi jucare de fiecare jucator. Se va afisa pe cate o linie numele jucatorului, urmat de numarul de maini ramase (separate prin spatiu) dupa cum urmeaza incepand cu stringul "Clasament nume_masa".
. ​ Mențiuni sortare​ :
● Sortarea se va face utilizând o noua lista. Lista va fi construită sortată
descrescător în funcție de clasamentul jucătorilor, prin inserarea
ordonata, succesiva jucătorilor.
● În cazul în care doi jucători au același număr de mâini rămase pentru a
fi jucate, compararea dintre cei doi se va face lexicografic, in funcție de
numele acestora, folosind ordinea din tabela ASCII. (ex.: “Ion” <
“Ionela”, “Andrei” < “Bogdan”, “Ion” > “IoN”)
● În cazul în care afișarea clasamentului se realizează prin construirea
unui vector și sortarea acestuia, soluția pentru testul respectiv va fi
punctată la jumătate din valoarea sa.

7.inchide[nume_masa] - Apelând evenimentul “închide nume_masa”, se dorește desființarea (ștergerea) mesei primita ca parametru. Lista destinată acelei mese va fi ștearsă din memorie, iar jucătorii aflați la masa respectiva vor fi redistribuiți la mese după cum urmează:
  ● Se vor parcurge mesele de la început spre sfârșit (în ordinea meselor primite în fișierul de configurație)
  ● Dacă masa curentă dispune de locuri libere, vor fi adăugați atâția jucători de la masa eliminată încât noua masă permite, în ordinea în care aceștia se aflau la masa închisă. Jucătorii vor fi adaugați la sfârșitul listei
  ● Procedeul se repetă, continuând la următoarea masă, până când toți jucătorii de la masa eliminată vor fi așezați la o noua masă
  
  
  
 ---Detalii despre implementare ---
 
 1. In functia CitireSala deschidem fisierul dat ca argument executabelului si citim datele configuratiile salii pe care trebuie sa o creem. Initial alocam memorie pentru sala (variabila room) si initializam cu 0 nrLocCrt...etc, pentru ca initial acestea sunt nule. Initializam o intructiune ciclica for care ne va crea un anumit numar de mese. In acest "for" alocam memorie pentru lista de mese si introducem fiecare celula ce reprezinta o masa la sfarsitul listei simplu inlantuite generice. De asemenea pentru fiecare masa mai pornim un "for" cu ajutorul careia creem lista simplu inlantuita generica cu santinela.Pentru fiecare liste de jucatori de la masa intializam o celula ce are informatia nula ce va reprezenta santinela(s), aceasta fiind inceputul si sfarsitul listei de jucatori de la fiecare masa.Fiecare jucator care e reprezentat de o anumita structura il introducem , de asmenea , la sfaristul listei de jucatori, inainte de celula ce reprezinta santinela.

2. In functia de AfisareSala, parcurgem lista de mese, precum si lista de jucatori din sala , scriind datele fiecareia in fisieruk output primit ca parametru(filename2).

3.Functia CautareMasa cautam in lista noastra o anumita masa, criteriul de cautare fiind numele acesteia.Daca o gaseste returneaza adresa acesteia.

4.Functia CautareJucator, de asemenea, cauta un anumit jucator la o anumita masa din toata sala si returneaza adresa celulei respective, parametrul de cautare fiind numele jucatorului primit ca parametru. In caz ca nu exista masa data ca parametru va insera in fisierul primit ca parametru ca masa respectiva nu exista.La fel, va afisa un mesaj si pentru jucator in caz ca nu exista.

5.Functia Noroc, adauga un anumit numar dat ca parametru la int -ul nrMaini din structura unui anumit jucator dat ca parametru.

6.Functia EliminaJucator elimina un anumit jucator din lista jucatorilor de la o anumita masa,precum si decrementeaza numarul locurilor curente in sala.

7.Functia EliminareMasa, de asemenea elimina o anumita masa din lista de mese din sala, precum si scade din numarul locurilor maxime din sala, numarul locurilor maxime de la masa respectiva.

8.Functia ghinion localizeaza un anumit jucator si scade din nrMaini un anumit numaru primit ca parametru.Daca nrMaini a jucatorului respectiv devine 0 , acesta este eliminat de la masa cu ajutorul functiei EliminareJucator. In caz ca la masa respectiva, in urma operatiilor de eliminare a jucatorilor, numarul jucatorilor devine 0, si aceasta masa este eliminata din lista de mese.In caz ca au fost eliminare toate mesele, se elibereaza si sala.

9.Functia TURA, executa o rotatie spre dreapta a jucatorilor de la masa data ca parametru si decrementeaza nrMaini a tuturor jucatorilor de la masa respectiva. Mai intai efecutam operatia de rotatie. Cu ajutorul unui for gasim ultimul jucator din lista, dupa care refacem legaturile acestuia, precum si cele a santinelei si a primului jucator. Dupa parcurgem toata lista de jucaotori si decrementam nrMaini.In continuare, la fel ca si la functia gihinion, daca nrMaini a unui jucator devine 0 sau numarul de jucator de la o masa devine 0, sunt eliminati, jucatorul ,respectiv si masa.

10.In functia TuraCompleta apelam functia TURA care o implementam pentru fiecare masa din sala.

11.Functia ALocareCel aloca memorie pentru fiecare celula a listei noi create in care vom insera jucatorii de la o masa sortati.

12.In functia sortedInsert comparam jucatorii de la o masa si ii introducem in ordine descrescatoare, in caz ca acestea sunt egale le comparam dupa numele acestora.
Lista noua va fi o lista simpla inlantuita.In general, tratam 3 cazuri:
a)Initial lista va fi goala, respectiv functia va insera primul jucator la inceputul listei.
b)In caz ca jucatorul primit ca parametru are nrMaini mai mare ca primul jucator din noua lista creata, acesta va fi inserat inainte acestuia, adica la inceputul listei, celalat devenind urmatorul.In caz ca nrMaini sunt egale, functia le va compara dupa nume, urmarind aceleasi principiu.
c)In caz ca elemntul nou introdus e mai mic ca primul, cu ajutorul unui for parcurgem lista noua creata atata timp cat nu vom gasi un element din lista sortata care va fi mai mic ( dupa nrMaini sau nume,daca e cazul), inserandul inaintea acestuia.Acesta fiind principul de baza de functionare a acestei functii.

13.Functia insertionSort are rolul de a selecta fiecare jucaotor din lista respectiva de jucatori si de al insera in locul potrivit in lista noua creata cu ajutorul functiei sortedInsert. Dupa care printeaza intr-un fisier primit ca parametru clasamentul acesteia in ordinea descrescatoare.

14.In functia clasament, apelam functia CautareMasa, pentru a gasi adresa mesei in care vrem sa realiza operatiunea de afisare in fisier a clasamentului in ordine descrescatoare, cu ajutorul functiei insertionSort.

15.Cu ajutorul functiei inchide_masa, eliminam o anumita masa cu un nume primit ca parametru si repartizam jucatorii de la masa respectiva la altele.Initial verificm daca avem locuri disponibile sala cu ajutorul unui formule. Dupa verificam daca numarul curent de jucatori de la masa pe care vrem s-o eliminam nu e mai mare ca locurile disponibile din sala pentru a putea a determina daca putem efectua aceasta operatie. Prin operatia de egalare a numarului maxim de jucatori cu numarul curent de jucatori am indicat ca la aceasta masa este imposibil de adaugat jucatori, adica am neutralizato, salvand numarul maxim de jucaotri intr-o variabila (z). Avem nevoie de acesta operatie pentru a sari peste aceasta masa in for-ul ce parcurge toate mesele din lista si gaseste locuri libere pentru a repartiza jucatorii de la masa pe care vrem s-o inchidem.In caz ca am gasit o masa cu locuri disponibile, introducem cate un jucator in lista jucatorilor de la masa respectiv unul cate unul, atat timp cat avem locuri disponibile prin refacerea legaturilor si adaugarea acestoa la sfarsitul listei.In caz ca nu mai sunt locuri disponibile, ne deplasam catre urmatoarea masa pentru a introduce jucatorii ramasi daca mai sunt locuri libere.Si in cele din urma, dupa ce am repartizat toti jucatorii, eliberam masa.

16.In main am creat niste var de tip char* si respectiv le-am alocat pentru a salva in ele elementele citite din fisierul2 primit ca parametru in care avem indicate comenzile.Apoi cu ajutorul instructionilor if apelam fiecare functie necesara ori de cate ori avem nevoie.

17.Cu ajutorul functiilor freeJucator , freeMasa, freeSala si freeSortedList eliberam toata memoria alocata pentru acestea. 
