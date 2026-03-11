int* funcionBuena() {
    int* x = new int(50);
    return x;
}

int* funcionMala() {
    int x = 50;
    return &x;
}