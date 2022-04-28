struct row{
    /*
    mpost = My position
    npost = Next position
    */
    //We must be careful with the padding 
    //https://www.geeksforgeeks.org/is-sizeof-for-a-struct-equal-to-the-sum-of-sizeof-of-each-member/
    int mpos,npos;
    short int sourceid,dstid,hod;
    float mean;
};

struct hashrow{
    /*
    Este no puede ser un short int porque este guarda las posiciones
    y las posiciones llegan hasta casi seis millones
    que es un número que no puede guardar un short int
    */
    int img;
};

struct sharerow{
    short int sourceid,dstid,hod;
};