#include <stdio.h>
#include <stdlib.h>
#include "fun.h"

link root ,z;//κενος κομβος


/*βοηθιτικη συναρτισι η οποια διμιουργει ενα κομβο του δεντρου ,βαζει
ολλα τα στιχια του στις καταλιλες θεσεις και επιστρεφει την διευθινση του*/
link New(int data, link left, link right, link parent, Color color, Side side) {
    link x = malloc(sizeof(RedBlackTree));
    x->data = data;
    x->left = left;
    x->right = right;
    x->parent = parent;
    x->color = color;
    x->side = side;
    return x;
}

/*βοηθιτικη συναρτισι που αλλαζει χροματα στον πατερα και
στους γιους(καλειτε οταν ο θειος ειναι κοκκινος)*/
void ColorRotation(link parent) {
//επιδι η ριζα πρεπει να ειναι παντα μαυρη,ο πατερας γεινετε κοκκινος οταν δεν ειμαστε στην ριζα
    if(parent != root)
        parent->color = red;//ο πατερας γεινετε κοκκινος
    //οι δυο γιοι του γινονται μαυροι
    parent->left->color = black;
    parent->right->color = black;
}

/*βοηθιτικη συναρτισι που αλλαζει χροματα στον πατερα και
στους γιους(καλειτε οταν ο θειος ειναι μαυρος(αφου προτα γεινουν τα καταλιλα rotations))*/
void ColorChangeNodeRotation(link parent) {
    parent->color = black;//ο πατερας γινετε μαυρος
//και οι δυο γιοι του γινονται κοκκινοι
    parent->left->color = red;
    parent->right->color = red;
}

/*οι κομβοι πριν κανουν αριστερο rotation διχνουν προτα στους σωστους γονεις +
περνουν σοστες τιμες στην τιμη side αφου καποιοι απο αριστερα γινονται δεξια
παιδια ή και το αντιθετο*/
void LeftRotationParentChange(link h) {
    link x = h->right;//x = δεξι παιδι του h 
    if(x->left != z) {/*επειδι ο κομβος z δεν διχνει σε κανενα πατερα και
    εχει σαν τιμη δικτη το NULL περνω περιπτοσεις (αμμα το x εχει αριστερο παιδι που δεν ειναι z)*/
        x->left->parent = h;//ο πατερας του αριστερου παιδιου του x διχνει στο h
        x->left->side = right;//και μεταγενεστερα γινετε απο αριστερο δεξι παιδι
    }
    x->parent = h->parent;//ο πατερας του x διχνει στον πατερα του h
    if(x->parent != NULL)//αν τορα το h δεν ειναι ο προτος κομβος του δεντρου(η ριζα) και εχει πατερα
        if(h->side == right) {//αν το h ειναι δεξι παιδι
            x->parent->right = x;//τοτε ο πατερας του h εχει πλεον σαν δεξι παιδι το x 
            x->side = right;//και το x εχει σαν πλιροφορια οτι ειναι δεξις κομβος
        }
        else {//αν το h ειναι αριστερο παιδι
            x->parent->left = x;//τοτε ο πατερας του h εχει πλεον σαν αριστερο παιδι το x 
            x->side = left;//και το x εχει σαν πλιροφορια οτι ειναι αριστερος κομβος
        }
    else {/*αν ο πατερας του x ειναι το κενο τοτε ειναι η ριζα του δενρου
    διλαδι ο προτος κομβος*/
        x->side = -1;//επιδι ειναι ριζα δεν εχει καπιο side (left-right)
        root = x;//το root διχνει στην καινουρια ριζα του δεντρου
    }
    h->parent = x;//ο πατερας του h ειναι το x που πριν ηταν το δεξι παιδι του
    h->side = left;//και επιδι γινετε αριστερο παιδι του x αλλαζει η πληροφορια του στο side
}

/*οι κομβοι πριν κανουν δεξι rotation διχνουν προτα στους σωστους γονεις +
περνουν σοστες τιμες στην τιμη side αφου καποιοι απο αριστερα γινονται δεξια
παιδια ή και το αντιθετο*/
void RightRotationParentChange(link h) {
    link x = h->left;//x = αριστερο παιδι του h 
    if(x->right != z) {/*επειδι ο κομβος z δεν διχνει σε κανενα πατερα και
    εχει σαν τιμη δικτη το NULL περνω περιπτοσεις (αμμα το x εχει δεξι παιδι που δεν ειναι z)*/
        x->right->parent = h;//ο πατερας του δεξιου παιδιου του x διχνει στο h
        x->right->side = left;//και μεταγενεστερα γινετε απο δεξι αριστερο παιδι
    }
    x->parent = h->parent;//ο πατερας του x διχνει στον πατερα του h
    if(x->parent != NULL)//αν τορα το h δεν ειναι ο προτος κομβος του δεντρου(η ριζα) και εχει πατερα
        if(h->side == right) {//αν το h ειναι δεξι παιδι
            x->parent->right = x;//τοτε ο πατερας του h εχει πλεον σαν δεξι παιδι το x 
            x->side = right;//και το x εχει σαν πλιροφορια οτι ειναι δεξις κομβος
        }
        else {//αν το h ειναι αριστερο παιδι
            x->parent->left = x;//τοτε ο πατερας του h εχει πλεον σαν αριστερο παιδι το x 
            x->side = left;//και το x εχει σαν πλιροφορια οτι ειναι αριστερος κομβος
        }
    else {/*αν ο πατερας του x ειναι το κενο τοτε ειναι η ριζα του δενρου
    διλαδι ο προτος κομβος*/
        x->side = -1;//επιδι ειναι ριζα δεν εχει καπιο side (left-right)
        root = x;//το root διχνει στην καινουρια ριζα του δεντρου
    }
    h->parent = x;//ο πατερας του h ειναι το x που πριν ηταν το αριστερο παιδι του
    h->side = right;//και επιδι γινετε δεξι παιδι του x αλλαζει η πληροφορια του στο side
}

/*συναρτιση που κανει αριστερι περιστροφη και επιστρεφη την διευθινση του καινουριου πατερα*/
link LeftRotation(link h) {
    LeftRotationParentChange(h);//συναρτιση για αλλαγη σε γονεις και πλευρες
    link x = h->right;//x = δεξι παιδι του h
    h->right = x->left;//δεξι παιδι του h γειντε το αριστερο παιδι του x
    x->left = h;//και αριστερο παιδι του x γεινετε το h
    return x;//επιστροφη διευθινσης του καινουριου πατερα
}

/*συναρτιση που κανει δεξια περιστροφη και επιστρεφη την διευθινση του καινουριου πατερα*/
link RightRotation(link h) {
    RightRotationParentChange(h);//συναρτιση για αλλαγη σε γονεις και πλευρες
    link x = h->left;//x = αριστερο παιδι του h
    h->left = x->right;//αριστερο παιδι του h γειντε το δεξι παιδι του x
    x->right = h;//και δεξι παιδι του x γεινετε το h
    return x;//επιστροφη διευθινσης του καινουριου πατερα
}

/*επιστρεφει την διευθινση του αδερφου του κομβου που δινω*/
link Sibling(link node) {
    if(node->side == right)//εαν ο κομβος που θελω να εξετασο ειναι δεξι παιδι
        return node->parent->left;//επιστρεφο την διευθινση του αριστερου παιδιου του πατερα του
    else//εαν ο κομβος που θελω να εξετασο ειναι αριστερο παιδι
        return node->parent->right;//επιστρεφο την διευθινση του δεξιου παιδιου του πατερα του
}

/*επιστρεφει το χρωμα του θειου του κομβου που στελνω*/
Color AuntColor(link node) {
    if(Sibling(node->parent)->color == black)//αν το χρομα του αδερφου του πατερα του κομβου που στελνω ειναι μαυρο
        return black;//επιστρεφω μαυρω
    else//αν απο την αλη το χρομα του αδερφου του πατερα του κομβου που στελνω ειναι κοκκινο
        return red;//επιστρεφω κοκκινο
}

/*σιναρτισι που τσεκαρι αν εχουμε δυο κομβους στην σιρα που ειναι
κοκκινοι και κανει τις καταλιλες αλλαγες για καθε περιπτωση
Σημειωση : ο κομβος που στελνο στην συναρτισι ειναι ο προτος κοκκινος 
διοτι η σιναρτισι αυτη καλειτε αναδρομικα*/
void check(link node) {
    link x;
//αν ο κομβος ειναι μαυρος ή ειναι η ριζα του δεντρου(διλαδι εχει για πατερα το NULL) ή εχει μαυρο πατερα
    if((node->parent == NULL) || (node->color == black) || (node->parent->color == black))
        return;//τοτε απλα τερματιζει η συναρτισει χορεις να κανουμε αλαγες
    if(AuntColor(node) == red) {//εαν ο θειος ειναι κοκκινος
        ColorRotation(node->parent->parent);//απλα κανο rotation στα χρωματα(στελνω τον παππου)
    }
    else {//αν ο θειος ειναι μαυρος
        if(node->parent->side == left) {
            if(node->side == left) {//left-left situation
                x = RightRotation(node->parent->parent);//δεξια περιστροφι (στελνω τον παπου του Node)
                ColorChangeNodeRotation(x);//αλλαγι χροματον (σαν πατερα παει η διευθινση x)
            }
            else {//left-right situation
                x = LeftRotation(node->parent);//αριστερη περιστροφι (στελνω τον πατερα του Node)
                x = RightRotation(x->parent);//δεξια περιστροφι (στελνω τον πατερα του x)
                ColorChangeNodeRotation(x);//αλλαγι χροματον (σαν πατερα παει η διευθινση x)
            }
        }
        else {
            if(node->side == left) {//right-left situation
                x = RightRotation(node->parent);//δεξια περιστροφι (στελνω τον πατερα του Νode)
                x = LeftRotation(x->parent);//αριστερη περιστροφι (στελνω τον πατερα του x)
                ColorChangeNodeRotation(x);//αλλαγι χροματον (σαν πατερα παει η διευθινση x)
            }
            else {//right-right situation
                x = LeftRotation(node->parent->parent);//αριστερη περιστροφι (στελνω τον παπου του Node)
                ColorChangeNodeRotation(x);//αλλαγι χροματον (σαν πατερα παει η διευθινση x)
            }
        }
    }
}

//ανταλαγη χρομάτων μεταξυ του κομβου που διχνει ο a και ο b
void collorswap(link a,link b) {
    Color temp = a->color;//αποθικευω προσορινα το χρομα του a δικτη
    a->color = b->color;//στο χρομα του a δικτη βαζο το χρομα του b δικτη
    b->color = temp;//στο χρομα του b δικτη βαζο το χρομα του a που το ειχα αποθικευσει στο temp
}

//αν εχει 2 παιδια που ειναι εξοτερικοι κομβοι
boll HasExternalChildren(link node) {
    if(node->left == z && node->right == z)//αν ο κομβος εχει για αριστερο και δεξι παιδι το NULL κομβο z
        return true;//επιστρεφει αλιθης
    else//αλιος
        return falsh;//επιστρεφει ψευδεις
}

/*συναρτισι που επιστρεφει την διευθινση της ριζας (root) και συνεχιζει 
μεχρει να μην υπαρχει Doubleblack και καλιτε οταν προτοεμφανιζετε το Doubleblack
Σημειοση : πριν καλεσο αυτην την σιναρτιση εχω βαλει τον κομβο που στελνω εδω
να κοιταει στον πατερα για να μπορο να εχο προσβασει σε καποιους κομβους παρολα αυτα
επειδι δεν θα λιτουργουσε σοστα για αυτο βαζο τον πατερα του DB να κοιταει τον κομβο
z ετσει ωστε να γινουν σοστα τα rotations και μετα την συναρτισι αυτη αποδεσμευω τον χορο
του Node που εστειλα εξαρχεις εδω*/
link DBcheck(link node) {
    link curent = node;
//αν ο κομβος ειναι DB και εχει 2 παιδια που ειναι z τοτε
    if(node->color == doubleblack && HasExternalChildren(node) == true) {
        if(node->side == left)//αν ειναι ο κομβος αριστερο παιδι
            node->parent->left = z;//τοτε ο πατερας του κομβου θα εχει αριστερο παιδι το z
        else//αν ειναι ο κομβος δεξι παιδι
            node->parent->right = z;//τοτε ο πατερας του κομβου θα εχει δεξι παιδι το z
    }
    while(curent->color == doubleblack) {//οσο εχω DB στο δεντρο
        if(Sibling(curent)->color == black) {//αν ο αδερφος του DB ειναι μαυρος
            //αν του αδερφου του τα παιδια ειναι μαρια
            if(Sibling(curent)->left->color == black && Sibling(curent)->right->color == black) {
                Sibling(curent)->color = red;//κανω τον αδερφο του κοκκινο
                curent->color = black;//τον DB τον κανω μαυρο
                if(curent->parent->color == red)//αν ο πατερας του ειναι κοκκινος τον κανο μαυρο
                    curent->parent->color = black;
                else {//αν ο πατερας του ειναι μαυρος τον κανω DB
                    curent->parent->color = doubleblack;
                    curent = curent->parent;//αποθικευ στο current την διευθινση του πατερα για να τον εξετασο
                }             
            }
            else if(curent->side == left) {//αν ο DB ειναι αριστερο παιδι
                if(Sibling(curent)->right->color == red) {//αν ειναι κοκκινο το δεξι παιδι του αδερφου του DB
                    //αλλαγη χρωματον μεταξι αδελφου και πατερα του DB
                    collorswap(Sibling(curent),curent->parent);
                    Sibling(curent)->right->color = black;//μαυρο χρωμα στον κοκκινο γιο
                    curent->color = black;//αφερεση DB
                    LeftRotation(curent->parent);//αριστερι περιστροφη του πατερα(περιστροφη προς το DB)
                }
            //αν εχει μαυρο αδερφο και το χρομα του αριστερου παιδιου του αδερφουτου ειναι κοκκινο    
                else if(Sibling(curent)->right->color == black && Sibling(curent)->left->color == red) {
                    //ανταλαγη χρωματον μεταξυ αδερφου του DB με το αριστερο παιδι του αδερφου του DB
                    collorswap(Sibling(curent),Sibling(curent)->left);
                    RightRotation(Sibling(curent));//δεξια περιστροφη του αδερφου του DB(αντιθετα απο τον DB)
                }
            }
            else if(curent->side == right) {//αν ο DB ειναι δεξι παιδι
                if(Sibling(curent)->left->color == red) {//αν ειναι κοκκινο το αριστερο παιδι του αδερφου του DB
                    //αλλαγη χρωματον μεταξι αδελφου και πατερα του DB
                    collorswap(Sibling(curent),curent->parent);
                    Sibling(curent)->left->color = black;//μαυρο χρωμα στον κοκκινο γιο
                    curent->color = black;//αφερεση DB
                    RightRotation(curent->parent);//δεξια περιστροφη του πατερα(περιστροφη προς το DB)
                }
            //αν εχει μαυρο αδερφο και το δεξι παιδι του αδερφου του εχει χρομα κοκκινο
                else if(Sibling(node)->left->color == black && Sibling(node)->right->color == red) {
                    //ανταλαγη χρωματον μεταξυ αδερφου του DB με το δεξι παιδι του αδερφου του DB
                    collorswap(Sibling(curent),Sibling(curent)->right);
                    LeftRotation(Sibling(curent));//αριστερη περιστροφη του αδερφου του DB(αντιθετα απο τον DB)
                }
            }
        }
        else if(Sibling(curent)->color == red) {//αν ο αδερφος του DB ειναι κοκκινος
            if(curent->side == left) {//αν ο DB ειναι αριστερα
            //ανταλαγη χρωματων μεταξυ αδερφου και πατερα του DB
                collorswap(Sibling(curent),curent->parent);
                LeftRotation(curent->parent);//αριστερη περιστροφη του πατερα του DB (περιστροφη προς το DB)
            }
            else if(curent->side == right) {//αν ο DB ειναι δεξια
                //ανταλαγη χρωματων μεταξυ αδερφου και πατερα του DB
                collorswap(Sibling(curent),curent->parent);
                RightRotation(curent->parent);//δεξια περιστροφη του πατερα του DB (περιστροφη προς το DB)
            }

        }
    }
    return root;//επιστροφη της ριζας
}

/*κανει καταλιλες αλαγες αμμα το στιχιο δεν εχει παιδια z για να μπορεσο να παρο περιπτοσεις
και επιστρεφει την διευθινση του στιχειου*/
link findkey(link current,int item) {
    link oldnode;
    if(current->data == item) {//αν βρω το στιχειο
        if(HasExternalChildren(current) == true) {//αν εχει 2 παιδια που ειναι z τοτε απλα το επιστρεφω
            return current;
        }
        else {//αν βρο το στιχειο και δεν εχει 2 παιδια που ειναι z
            do{
                oldnode = current;
                if(current->right != z) {//αν εχει κομβο στα δεξια
                    current = current->right;//περνει την διευθινση του δεξιου παιδιου
                    while(current->left != z) {//μεχρι να φτασει τερμα αριστερα
                        current = current->left;//περνει την διευθινση του αριστερου παιδιου
                    }
                }
                else {//αν δεν εχει κομβο δεξια παει αριστερα
                    current = current->left;//περνει την διευθινση του αριστερου παιδιου
                    while(current->right != z) {//μεχρει να φτασει τερμα δεξια
                        current = current->right;//περνει την διευθινση του δεξιου παιδιου
                    }
                }
                //ανταλαγι παλιας τιμης με καινουριας(αμεσος μεγαλυτερης ή αμεσος μικροτερης)
            /*στον παλιο κομβο που εχο βρει το στιχιο αποθικευω το αμεσος μικροτερο η αμεσος το αμεσος μεγαλιτερο*/
                oldnode->data = current->data;
            }while(HasExternalChildren(current) == falsh);//οσο δεν ειμαι σε κομβο με παιδια z(NULL)
            return current;//επιστρεφο την διευθινση του κομβου που θα διαγραφτει
        }
    }
    else if(current->data > item)//αν ειναι μικροτερο παο αριστερα
        return findkey(current->left,item);
    else//αν ειναι μεγαλιτερο παο δεξια
        return findkey(current->right,item);
}

/*αν το Node ειναι κοκκινο*/
void case1(link node) {
    if(node->side == left)//αν ο κομβος που θα δαγρψω εινα αριστερο παιδι
        node->parent->left = z;//βαζω το αριστερο παιδι του πατερα να ειναι Z (NULL)
    else//αν ειναι δεξι παιδι
        node->parent->right = z;//βαζω το δεξι παιδι του πατερα να ειναι Z (NULL)
    free(node);//αποδεσμευση χωρου
}

/*συναρτισι που επιστρεφει το χρομα του αριστερου παιδιου*/
Color CLChild(link parent) {
    return parent->left->color;
}

/*συναρτισι που επιστρεφει το χρομα του δεξιου παιδιου*/
Color CRChild(link parent) {
    return parent->right->color;
}

/*αρχικοποιοιση της διευθινσης root και επιστροφη αυτης + αρχικοποιοιση του κενου κομβου z*/
link Initialize() {
    root = New(-1, NULL, NULL, NULL, white, -1);
    z = New(-1, NULL, NULL, NULL, black, -1);
    return root;
}

/*σιναρτισι που επιστρεφει την διευθινση της ριζας + εισαγο κομβο + ελενχο αν υπαρχουν 2 κοκινα στην σιρα*/
link InsertKey(link node, int item) {
    link newnode ,current = node;


    if(current->color == white) {//αν το χρομα του Node ειναι ασπρο διλαδι ειναι το προτο στιχειο που εισαγο
        free(root);//αποδεσμευο τον χορο που διχνει το root
        root = New(item, z, z, NULL, black, -1);//το root διχνει στον προτο κομβο του δεντρου
    }
    else if(current->data > item) {//αν το στιχειο που θελο να βαλω ειναι μικροτερο απο αυτο που ειμε τορα
        if(current->left != z) {//εαν αριστερα δεν εχει το z κομβο
            InsertKey(current->left, item);//παο να δω αριστερα
            check(current);//ελενχω αν υπαρχουν 2 κοκκινα στην σιρα
        }
        else {//εαν αριστερα εχει το z κομβο σημαινει οτι μπορο να βαλο καινουριο κομβο
            newnode = New(item, z, z, current, red, left);//διμιουργια καινουριου κομβου στον οποιο διχνει ο δικτις newnode
            current->left = newnode;//βαζω το current να εχει για αριστερο παιδι το newnode
            check(newnode);//ελενχω αν υπαρχουν 2 κοκκινα στην σιρα
        }    
    }
    else if(current->data < item){//αν το στιχειο που θελο να βαλω ειναι μεγαλιτερο απο αυτο που ειμε τορα
        if(current->right != z) {//εαν δεξια δεν εχει το z κομβο
            InsertKey(current->right, item);//παο να δω δεξια
            check(current);//ελενχω αν υπαρχουν 2 κοκκινα στην σιρα
        }
        else {//εαν δεξια εχει το z κομβο σημαινει οτι μπορο να βαλο καινουριο κομβο
            newnode = New(item, z, z, current, red, right);//διμιουργια καινουριου κομβου στον οποιο διχνει ο δικτις newnode
            current->right = newnode;//βαζω το current να εχει για δεξι παιδι το newnode
            check(newnode);//ελενχω αν υπαρχουν 2 κοκκινα στην σιρα
        }
    }
    return root;//επιστρεφω την ριζα
}

/*συναρτιση η οποια επιστρεφη την ριζα + περνει περιπτοσεις + καλει συναρτισει που με βασει καπιες περιπτοσεις εξαφανιζει το DB*/
link RemoveKey(link node, int item) {
    link deletnode,x;
    node = findkey(node,item);//Νode = η διευθινση του στιχιου που θα διαγραφτει
    if(node == root) {//αν εχει μινι μονο η ριζα και πρεπει να διαγραφτη
        free(node);
        root = New(-1, NULL, NULL, NULL, white, -1);//βαζο το root να βλεπει σε εναν κενο κομβο (σαν το initialize)
        return root;
    }
    else if(node->color == red) {//αν ειναι κοκκινο απλα τον διαγραφο
        case1(node);
        return root;
    }
    else if(node->color == black) {//αν ειναι μαυρος
        node->color = doubleblack;//τον κανο doublevlack
        deletnode = node;
        x = DBcheck(node);//εξαφανιζο το doubleblack
        free(deletnode);//απλευθερονο τον κομβο που ηταν doublevlack
        return x;
    }
}

/*εκτυποσει με αυξουσα σειρα*/
void InOrder(link node) {
    if(node == z || node == NULL)//αν φτασο στο τελος του δεντρου (στο z) δεν εκτιπονω τιποτα
        return;
    else {
        InOrder(node->left);//παο στο αριστερο υποδεντρο
        if(node->color == black)//εαν το χρωμα ειναι μαυρο
            if(node->side == left)
                printf("(%d,black,left) | ", node->data);
            else if(node->side == right)
                printf("(%d,black,right) | ", node->data);
            else
                printf("(%d,black,root) | ", node->data);
        else if(node->color == red)//εαν το χρωμα ειναι κοκκινο
            if(node->side == left)
                printf("(%d,red,left) | ", node->data);
            else if(node->side == right)
                printf("(%d,red,right) | ", node->data);
        else
            printf("(%d,white,root) | ", node->data);
        InOrder(node->right);//παο στο δεξι υποδεντρο
    }
}

/*επιστρεφει true ή falsh αναλογα με τον υπαρχει ή οχι το στιχειο που δινετε*/
boll Search(link curent, int data) {
    if(curent->color == white) {//αν δεν εχω βαλει κακενα στιχειο στο δετρο
        return falsh;//επιστρεφω falsh
    }
    else if(curent == z) {//αν εχω φτασει στα NULL κομβους
        return falsh;//επιστρεφω falsh
    }
    else if(curent->data == data) {//αν βρω το στιχειο
        return true;//επιστρεφω true
    }
    else if(curent->data > data) {//αν το στιχειο ειναι μικροτερο παο να ψαξω αριστερα
        return Search(curent->left,data);
    }
    else//αν το στιχειο ειναι μεγαλιτερο παο να ψαξω δεξια
        return Search(curent->right,data);
}
