Professor::Professor(string name)
          : Person(name){}

void Professor::is_can_borrow_prof(Document *duc){
    if (owned_duc.size() > MAX_CAPACITY_FOR_BORROW_PROF)
        throw runtime_error("Maximum number of allowed borrows exceeded\n");
}