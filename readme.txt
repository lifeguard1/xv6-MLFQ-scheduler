README - NIKOLAOS KOUTSOUNIS (sdi2300091)

ΥΛΟΠΟΙΗΣΗ ΝΕΟΥ SYSCALL(ps.c)

Για αρχη προσθεσαμε στην δομη proc τα εξης attributes:
- priority ωστε να ξερουμε σε ποια ουρα προτεραιοτητας βρισκεται
- cticks προσδιοριζει ποσα timer ticks εχουν γινει στο current queue
- wticks προσδιοριζει ποσα timer ticks εχουν γινει σε κατασταση wait(το χρησιμοποιουμε ωστε να μην γινει starvation)

Στην allocproc τα αρχικοποιουμε τα νεα attributes με 0
Στην freeproc τα μηδενίζουμε

Νεα συναρτηση all_procinfo:
- Ειναι μια βοηθητικη συναρητηση μεσα στο proc.c ωστε να κανει iterate σε ολα τα non-UNUSED processes και να αντιγραψει τα στοιχεια καθε process στην δομη pstat. Επειτα αντιγραφει την γεμισμενη δομη που βρισκεται σε kernel space στο user space το οποιο δωθηκε ως argument στην συναρτηση για να ξερουμε που να το αντιγραψουμε με την copyout.

Νεα συναρτηση sys_getpinfo:
- Ειναι το kernel syscall που απλα καλει την all_procinfo δινοντας ως argument την destination user address.

Νεο αρχειο ps.c:
- Αφορα την εντολη ps οπου θα μπορει να καλει ο χρηστης ωστε να μεσω της προηγουμενης sys_getpinfo εκτυπωνονται10 τα στοιχεια των processes.

trap.c:
- Οταν γινεται timer interrupt τοτε πρεπει να αυξηουμε τα current used ticks του process και να ελεγξουμε εαν εφτασε στο μεγιστο, ωστε αν ναι καλουμε την yield. Επισης για καθε αλλο process που ειναι RUNNABLE αυξανουμε τα waiting ticks ωστε να αποφυγουμε starvation προκαλωντας promote process σε higher priority level.

proc.c:
Στην συναρτηση yield() η οποια καλειται μονο οταν καποιο process εξαντλει τα cticks του.

Στην συναρτηση scheduler() αλλαξαμε τα εξης:
- Για αρχη εχουμε ενα εξωτερικο loop που τρεχει μεταξυ των queues και ενα inner loop που τρεχει τα processes. Οταν μια διεργασια σταματησει να τρεχει τοτε επαναφερουμε το loop και ξαναξεκιναμε απο priority level 0.
