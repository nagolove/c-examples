class IVoxel {
public:
    virtual void dosmthng() = 0;
    virtual ~IVoxel() = 0;
};

class BigVoxel: public IVoxel {
public:
    // конструктора может не быть?
    BigVoxel() {
    };
    void dosmthng() override {
        //some code
    }
    ~BigVoxel() override {
        //some code
    }
};

IVoxel *vox = new BigVoxel();

