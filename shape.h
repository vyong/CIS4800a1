typedef struct shapeNode {
    int shape, colour, iterations;
    double size;
    struct shapeNode * next;
    
    //Location variables
    double inx, iny, inz;
    double xoff, yoff, zoff;
    
    //Rotate variables
    double inxr, inyr, inzr;
    double xroff, yroff, zroff;
    
    //Scale variables
    double inxs, inys, inzs;
    double xsoff, ysoff, zsoff;
    
} Shape;