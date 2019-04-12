#ifndef BAT_H
#define BAT_H


class Bat
{
    public:
        Bat();
        virtual ~Bat();

        void set_type(int t){
            type = t;
        }

        int get_type(){
            return type;
        }

        void set_id(int t){
            id = t;
        }

        int get_id(){
            return id;
        }

    protected:

    private:

    int type;
    int id;
};

#endif // BAT_H
