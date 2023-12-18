# UserSched
Implementati un user weighted round-robin scheduler: algoritmul
parcurge lista de utilizatori cu procese gata de executie n ordine round-robin. O dată ales un ıı
utilizator, algoritmul alege un proces apartinând acestuia si l lasă să se execute un timp finit. ıı
Utilizatorii au o pondere asociată care dictează timpul de executie permis.

Pentru a scrie codul pentru un programator de utilizatori cu algoritmul round-robin ponderat în Linux, veți avea nevoie de următoarele componente:

    1. Structuri de date:
        O structură pentru a reprezenta un proces. Aceasta ar trebui să includă cel puțin un câmp pentru a indica dacă procesul este gata de executie și un câmp pentru a stoca timpul de rulare necesar.
        O structură pentru a reprezenta un utilizator. Aceasta ar trebui să includă o listă de procese și o pondere asociată.
struct proces {
	trulare;
	tsleep;
	starea;
	user;
}

Trebuie sa ne luam de la modelul job_schedulning -> batch
Sau mai hard de adaugat not procese 

    2. Funcții pentru gestionarea utilizatorilor:
        O funcție pentru a crea un nou utilizator. Aceasta ar trebui să aloce memorie pentru structura de utilizator și să inițializeze câmpurile corespunzătoare.
        O funcție pentru a adăuga un utilizator la lista de utilizatori.
Simplificare: Un utilizator un proces,
Dupa: Un utilizator mai multe procese,
Dupa: Politici de asteptare a utilizatorului

    3. Funcția de programare:
        Aceasta este funcția principală care implementează algoritmul round-robin ponderat. Ar trebui să parcurgă lista de utilizatori și să aleagă un proces gata de executie pentru fiecare utilizator. Timpul de rulare permis pentru fiecare proces ar trebui să fie proporțional cu ponderea utilizatorului.

    4. Funcții de gestionare a timpului:
        Va trebui să aveți o funcție pentru a obține timpul curent și o funcție pentru a aștepta o anumită perioadă de timp. Acestea sunt necesare pentru a asigura că fiecare proces rulează doar pentru timpul permis.

-- NU e important doar daca in struct punem size (nu trebuie)
    5. Funcții de gestionare a contextului:
        Va trebui să aveți o funcție pentru a salva contextul curent (starea registrului și stiva) și o funcție pentru a restaura un context salvat. Acestea sunt necesare pentru a comuta între procese.

Notite prof:
while (i++ < 20K)
{
	process_time(); -> random
	sleep_random(); -> random
}

Trebuie sa avem un run que si wait que
Generare un nr aleator de procese si sa face mun grafic cu avg time pentru mai multe procese
