using namespace std;

node* list::findnode(int ind) {
    node *found;
    if (ind <= N/2) {
        node *p = head->next;
        for (int j = 0; j < ind; j++) {
            p = p->next;
        }
        found = p;
    }
    else {
        node *p = head->prev;
        for (int j = N; j > ind; j--) {
            p = p->prev;
        }
        found = p;
    }
    return found;
}
