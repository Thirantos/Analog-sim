#include <vector>

class Part;

class Port{
public:
    Part* part;
    int port;

    Port(Part* p, int port){
        this->part = p;
        this->port = port;
    }
};

class Part{
public:
    std::vector<float> input;
    std::vector<Port> output;

    virtual void onUse(){}

    void next(Part* part, int port){
        Port p(part, port);
        output.push_back(p);
    }

};

class Dial : public Part{
public:
    float voltage;

    void onUse() override {
        for(auto& port : output){
            port.part->input.insert(port.part->input.begin() + port.port, voltage);
            port.part->onUse();
        }
    }
};

class Sensor : public Part{
public:
    void onUse() override {
        std::string str;
        for (float val : input) {
            str += std::to_string(val) + " ";
        }
        std::cout << str << "\n";
    }
};

class Plus : public Part{
public:
    void onUse() override {
        if(input.size() != 2){return;}
        float voltage = input[0] + input[1];

        for(auto& port : output){
            port.part->input.insert(port.part->input.begin() + port.port, voltage);
            port.part->onUse();
        }

    }
};