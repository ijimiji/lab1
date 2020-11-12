#ifndef ID_H
#define ID_H
class UniqueID {
  protected:
    static int nextID;

  public:
    int value;
    UniqueID();
};

#endif
