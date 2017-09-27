using namespace std;

void list::push_front(const int &val) {
    node *p = new node(val);
    if (head->next == NULL) {
        head->next = p;
    }
    else {
        node *pp = head->next;
        head->next = p;
        p->next = pp;
    }
    N++;
    return;
}

void list::pop_front() {
    node *p = head->next;
    if (p->next == NULL) {
        head->next = NULL;
    }
    else {
        head->next = p->next;
        p->next = NULL;
    }
    delete p;
    N--;
    return;
}

const int & list::front() {
    node *p = head->next;
    return p->data;
}
