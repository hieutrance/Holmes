#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct shipinfo {
    string name;
    string day_in;
    string time_in;
    string day_out;    
    string time_out;
    int time;
    bool check_max;
};

//--check ship_name------------------
bool check_name(string str){
    size_t len = str.size();
    int n = static_cast<int>(len);
    bool check=true;
    

    for(int i=0 ; i<n ; i++){
        if(!(str[i]>='0' && str[i]<='9' || str[i]>='a' && str[i]<='z' || str[i]>='A' && str[i]<='Z'))
        {
        check = false;
            break;
        }
    }

    return check;

}


//-------------------------------------
bool check_date(string str) {
   bool checkday = true, checkmonth = true, check = true;
   string day = str.substr(0,2), month = str.substr(3,2);

   size_t position = str.find('?');

   if(position != std :: string :: npos){

    if(month == "??") checkmonth = true;
    
    if(month[0] == '?' && month[1] != '?') checkmonth = true;
    else
    if(month[0] != '?' && month[1] == '?'){
        if(month[0] == '0' ||
           month[0] == '1' ) checkmonth = true;
           else
           checkmonth = false;

         
    }

    if(day == "??") checkday = true;
    
    if(day[1] == '?' && day[0] != '?') checkday = true;
    else
    if(day[0] == '?' && day[1] != '?'){
        if(day[0] == '0' ||
           day[0] == '1' ||
           day[0] == '2' ||
           day[0] == '3' ) checkday = true;

           
           
    }
     size_t pos1 = day.find('?');
    if(!(pos1 != std :: string :: npos)){
        if(stoi(day) > 31) checkday = false;
    } 
    size_t pos2 = month.find('?');
    if(!(pos2 != std :: string :: npos)){
        if(stoi(month) > 12) checkmonth = false;
    }

    return (checkday & checkmonth);

   }
   else
   {
    if(stoi(month) > 12) check = false;
    if(month == "02") if(stoi(day) > 28) check = false;
    if(month == "04" ||
       month == "06" ||
       month == "09" ||
       month == "11" ){
        if(stoi(day) > 30) check = false;
        else
        check = true;
       }
    if(month == "01" ||
       month == "03" ||
       month == "05" ||
       month == "07" ||
       month == "08" ||
       month == "10" ||
       month == "12"){
        if(stoi(day) > 31) check = false;
        else
        check = true;
       }  

       return check; 
   }       
    }


//--------------------------------------
bool check_hour(string str){
    string hour, min;
    int HOUR, MIN;
    bool checkhour = true , checkmin = true, check = true;

    hour = str.substr(0,2);
    min = str.substr(3,2);

    size_t position = str.find('?');

    if(position != std :: string :: npos){
        if(hour == "??") checkhour = true;
        if(hour[0] == '?' && hour[1] != '?') checkhour = true;
        else
        if(hour[0] != '?' && hour[1] == '?'){
            if(hour[0] == '0' ||
               hour[0] == '1' ||
               hour[0] == '2' ) checkhour = true;
            else
            checkhour = false;   
        }

        if(min == "??") checkmin = true;
        if(min[0] == '?' && min[1] != '?') checkmin = true;
        else
        if(min[0] != '?' && min[1] == '?'){
            if(min[0] == '0' ||
               min[0] == '1' ||
               min[0] == '2' ||
               min[0] == '3' ||
               min[0] == '4' ||
               min[0] == '5' ) check = true;
            else
            check = false;
        }

        size_t pos1 = hour.find('?');
        if(!(pos1 != std :: string :: npos)){
            if(stoi(hour) > 23) checkhour = false;
        }

        size_t pos2 = min.find('?');
        if(!(pos2 != std :: string :: npos)){
            if(stoi(min) > 59) checkmin = false;
        }

        return (checkhour & checkmin);

    }
    else
    {
        if(stoi(hour) > 23) check = false;
        if(stoi(min) > 59) check = false;

        return check;
    }



    
}

//----------------------------------
int invalidTime(const string& schedule) {
    
int count=0;   
string shipnumber, token;
ifstream input(schedule);

   //------------------------ xu ly shipnumber

   for(int i=1 ; i<=4 ; i++) input >> shipnumber;
   if(shipnumber == "000") return -1;
   for(int i=0 ; i<3 ; i++){
        if(!(shipnumber[i] >= '0' && shipnumber[i]<= '9')) return -1;
    }    

    //------------------------------- xu ly tu dong thu 2 

    shipinfo ship[100];
    int num = stoi(shipnumber);

    for(int i=1 ; i<= num ; i++){
    input >> ship[i].name >> ship[i].day_in >> ship[i].time_in >> token >> ship[i].day_out >> ship[i].time_out ;
    ship[i].name.erase(ship[i].name.end() - 1);
    }

    //---------------kiem tra ----------

for(int i=1 ; i<= num ; i++){
    if(check_name(ship[i].name)== 1 &&
       check_date(ship[i].day_in) == 1 &&
       check_hour(ship[i].time_in) == 1 &&
       check_date(ship[i].day_out) == 1 &&
       check_hour(ship[i].time_out) ==1 ) count++;

}

return count;
}  

//-------max time function----s--------

int count_day(string date_in , string date_out){

    int day_in = stoi(date_in.substr(0,2)), day_out = stoi(date_out.substr(0,2));
    
    int month_in = stoi(date_in.substr(3,2)), month_out = stoi(date_out.substr(3,2));
    int day;
    if(month_in == month_out){
        day = day_out - day_in -1;
    }
    else{
    if(month_in == 2){
            day = 28 - day_in + day_out;
    }

    if(month_in == 4 ||
       month_in == 6 ||
       month_in == 9 ||
       month_in == 11){
            day = 30 - day_in + day_out;
    }
    else
    {
        day = 31 - day_in + day_out;
    }

    for(int i= month_in + 1; i < month_out; i++){
        if(i == 2) day += 28;
        else
        if(i == 4 ||
           i == 6 ||
           i == 9 ||
           i == 11)
           day += 30;
        else
        day += 31;     
    }
    }

    return day;

}

int count_hour(string date_in , string time_in, string date_out ,  string time_out){
    int hour_in = stoi(time_in.substr(0,2)), hour_out = stoi(time_out.substr(0,2));
    
    int min_in  = stoi(time_in.substr(3,2)), min_out  = stoi(time_out.substr(3,2));

    if(date_in == date_out){
        return ((hour_out - hour_in -1)*60 + 60 - min_in + min_out);
    }
    else{
    int hour = 23 - hour_in + hour_out;
    int min = 60 - min_in + min_out;

    return (hour*60 + min);
    }
}

//--------------------------------
int max_hour(string date_in, string time_in, string date_out, string time_out){
    string hour_in = time_in.substr(0,2) , hour_out = time_out.substr(0,2);
    string min_in  = time_in.substr(3,2) , min_out  = time_out.substr(3,2);

// xu ly time_in
    if(hour_in == "??"){
        hour_in = "00";
    }
    else
    if(hour_in[0] == '?' && hour_in[1] != '?'){
        hour_in[0] = '0';
    }
    else
    if(hour_in[0] != '?' && hour_in[1] == '?'){
        hour_in[1] = '0';
    }

    if(min_in == "??"){  
        min_in = "00";
    }
    else
    if(min_in[0] == '?' && min_in[1] != '?'){
        min_in[0] = '0';
    }
    else
    if(min_in[0] != '?' && min_in[1] == '?'){
        min_in[1] = '0';
    }

// xu ly time_out
    if(hour_out == "??"){
        hour_out = "23";
    }
    else
    if(hour_out[0] == '?' && hour_out[1] != '?'){ //  ?X
        if(hour_out[1] == '0' ||
           hour_out[1] == '1' ||
           hour_out[1] == '2' ||
           hour_out[1] == '3' ){
            hour_out[0] = '2'; 
           }
        else{
            hour_out[0] = '1';
        }   
    }
    else
    if(hour_out[0] != '?' && hour_out[1] == '?'){ //  X? 
        if(hour_out[0] == '2') hour_out[1] = '3';
        else
        hour_out[1] = '9';
    }

    if(min_out == "??") min_out = "59";
    else
    if(min_out[0] == '?' && min_out[1] != '?'){
        if(min_out[1] == '0' ||
           min_out[1] == '1' ||
           min_out[1] == '2' ||
           min_out[1] == '3') min_out[0] = '2';
           else
           min_out[0] = '1';
    }
    else
    if(min_out[0] != '?' && min_out[1] == '?'){
        if(min_out[0] == '2') min_out[1] = '3';
        else
        min_out[1] = '9';
    }

    time_in[0]  = hour_in[0] ; time_in[1]  = hour_in[1] ;
    time_in[3]  = min_in[0]  ; time_in[4]  = min_in[1]  ;
    time_out[0] = hour_out[0]; time_out[1] = hour_out[1];
    time_out[3] = min_out[0] ; time_out[4] = min_out[1] ;

    return count_hour(date_in, time_in, date_out, time_out);

}

int max_day(string & date_in, string & date_out){
    string day_in = date_in.substr(0,2), month_in = date_in.substr(3,2);
    string day_out = date_out.substr(0,2), month_out = date_out.substr(3,2);

    // xu ly date_in -> dau date_in ve MIN 01/01

    if(month_in == "??"){ // month = ??
        month_in = "01";
        if(day_in == "??") day_in = "01";
        if(day_in[0] == '?' && day_in[1] != '?'){
            if(day_in[1] == '0') day_in[0] = '1';
            else
            day_in[0] = '0';
        }
    }
    else
    if(month_in[0] == '?' && month_in[1] != '?'){  //month = ?X
        if(month_in[1] == '0') month_in[1] = '1';
        else
        month_in[0] = '0';

        if(day_in == "??") day_in = "01";
        else
        if(day_in[0] == '?' && day_in[1] != '?'){
            if(day_in[1] == '0') day_in[0] = '1';
            else
            day_in[0] = '0';
        }
        else
        if(day_in[0] != '?' && day_in[1] == '?'){
            if(day_in[0] == '0') day_in[1] = '1';
            else
            day_in[1] = '0';
        }
    }
    else
    if(month_in[0] != '?' && month_in[1] == '?'){  // month = X?
        if(month_in[0] == '0') month_in[1] = '1';
        else
        month_in[1] = '0';

        if(day_in == "??") day_in = "01";
        else
        if(day_in[0] == '?' && day_in[1] != '?'){
            if(day_in[1] == '0') day_in[0] = '1';
            else
            day_in[0] = '0';
        }
        else
        if(day_in[0] != '?' && day_in[1] == '?'){
            if(day_in[0] == '0') day_in[1] = '1';
            else
            day_in[1] = '0';
        }        
    }

    // xu ly date_out dua dateout ve MAX = 31/12....

    if(month_out == "??"){
        month_out = "12";

        if(day_out == "??"){
            day_out = "31";
        }
        else
        if(day_out[0] == '?' && day_out[1] != '?'){
            if(day_out[1] == '0' || day_out[1] == '1'){
                day_out[0] = '3';
            }
            else
            {
                day_out[0] = '2';
            }
        }
        else
        if(day_out[0] != '?' && day_out[1] == '?'){
            if(day_out[0] == '3') day_out[1] = '1';
            else
            day_out[1] = '9';
        }
    }
    else
    if(month_out[0] == '?' && month_out[1] != '?'){
        if(month_out[1] == '0' ||
           month_out[1] == '1' ||
           month_out[1] == '2')
           {
            month_out[0] = '1';
            if(day_out == "??"){
                if(month_out == "11") day_out = "30";
                else
                day_out = "31";
            }
            else
            if(day_out[0] == '?' && day_out[1] != '?'){
                if(month_out == "11"){
                    if(day_out[1] == '0') day_out[0] = '3';
                    else
                    day_out[0] = '2';
                }
                else
                {
                    if(day_out[1] == '0' || day_out[1] == '1') day_out[0] = '3';
                    else
                    day_out[0] = '9';
                }
            }
           } 
           else
           {
            month_out[0] = '0';

            if(month_out == "02"){
                if(day_out == "??") day_out = "28";
                else
                if(day_out[0] == '?' && day_out[1] != '?'){
                    if(day_out[1] == '9') day_out[0] = '1';
                    else
                    day_out[0] = '2';
                }
                else
                if(day_out[0] != '?' && day_out[1] == '?'){
                    if(day_out[0] == '2') day_out[1] = '8';
                    else
                    day_out[1] = '9';
                }
            }  
            if(month_out ==  "04" ||  // month = 04 06 09 co 30 ngay
               month_out == "06" ||
               month_out == "09"){
                if(day_out == "??") day_out = "30";
                else
                if(day_out[0] == '?' && day_out[1] != '?'){
                    if(day_out[1] == '0') day_out[0] = '3';
                    else
                    day_out[0] = '2';
                }
                else
                if(day_out[0] != '?' && day_out[1] == '?'){
                    if(day_out[0] == '3') day_out[1] = '0';
                    else
                    day_out[1] = '9';
                }
            }

            if(month_out == "03" || // momth= 03, 05 ,07, 08 co 31 ngay
               month_out == "05" ||
               month_out == "07" ||
               month_out == "08" ){
                if(day_out == "??") day_out = "31";
                else
                if(day_out[0] == '?' && day_out[1] != '?'){
                    if(day_out[1] == '0' || day_out[1] != '1') day_out[0] = '3';
                    else
                    day_out[0] = '2';
                }
                else
                if(day_out[0] != '?' && day_out[1] == '?'){
                    if(day_out[0] == '3') day_out[1] = '1';
                    else
                    day_out[1] = '9';
                }
            } 

           }
    }
    else
    if(month_out[0] != '?' && month_out[1] == '?'){
            if(month_out[0] == '0'){
                month_out[1] = '9';  // month = 09
                if(day_out == "??") day_out = "30";
                else
                if(day_out[0] == '?' && day_out[1] != '?'){
                    if(day_out[1] == '0') day_out[0] = '3';
                    else
                    day_out[0] = '2';
                }
                else
                if(day_out[0] != '?' && day_out[1] == '?'){
                    if(day_out[0] == '3') day_out[1] = '0';
                    else
                    day_out[1] = '9';
                }
            }
            else
            if(month_out[0] == '1'){
                month_out[1] = '2';  // month = 12
                if(day_out == "??") day_out = "31";
                else
                if(day_out[0] == '?' && day_out[1] != '?'){
                    if(day_out[1] == '0' || day_out[1] != '1') day_out[0] = '3';
                    else
                    day_out[0] = '2';
                }
                else
                if(day_out[0] != '?' && day_out[1] == '?'){
                    if(day_out[0] == '3') day_out[1] = '1';
                    else
                    day_out[1] = '9';
                }
            }
        } 

//-----------------------

size_t pos1 = day_in.find('?');
size_t pos2 = month_in.find('?');

// ? co trong day | ko co trong month
if((pos1 != std :: string :: npos) && !(pos2 != std :: string :: npos)){
        if(day_in == "??") day_in = "01";
        else
        if(day_in[0] == '?' && day_in[1] != '?'){
            if(day_in[1] == '0') day_in[0] = '1';
            else day_in[0] = '0';
        }
        else
        if(day_in[0] != '?' && day_in[1] == '?'){
            if(day_in[0] == '0') day_in[1] = '1';
            else
            day_in[1] = '0';
        }    
}

pos1 = day_out.find('?');
pos2 = month_out.find('?');

if((pos1 != std :: string :: npos) && !(pos2 != std :: string :: npos)){
        if(month_out == "02"){
            if(day_out == "??") day_out = "28";
                else
                if(day_out[0] == '?' && day_out[1] != '?'){
                    if(day_out[1] == '9') day_out[0] = '1';
                    else
                    day_out[0] = '2';
                }
                else
                if(day_out[0] != '?' && day_out[1] == '?'){
                    if(day_out[0] == '2') day_out[1] = '8';
                    else
                    day_out[1] = '9';
                }
        }
        else
        if(month_out ==  "04" ||  // month = 04 06 09 co 30 ngay
               month_out == "06" ||
               month_out == "09"){
                if(day_out == "??") day_out = "30";
                else
                if(day_out[0] == '?' && day_out[1] != '?'){
                    if(day_out[1] == '0') day_out[0] = '3';
                    else
                    day_out[0] = '2';
                }
                else
                if(day_out[0] != '?' && day_out[1] == '?'){
                    if(day_out[0] == '3') day_out[1] = '0';
                    else
                    day_out[1] = '9';
                }
        }
        else
        if(month_out == "03" || // momth= 03, 05 ,07, 08 co 31 ngay
               month_out == "05" ||
               month_out == "07" ||
               month_out == "08" ){
                if(day_out == "??") day_out = "31";
                else
                if(day_out[0] == '?' && day_out[1] != '?'){
                    if(day_out[1] == '0' || day_out[1] != '1') day_out[0] = '3';
                    else
                    day_out[0] = '2';
                }
                else
                if(day_out[0] != '?' && day_out[1] == '?'){
                    if(day_out[0] == '3') day_out[1] = '1';
                    else
                    day_out[1] = '9';
                }
            }        
    }

    date_in[0] = day_in[0]; date_in[1] = day_in[1];
    date_out[0] = day_out[0]; date_out[1] = day_out[1];
    date_in[3] = month_in[0]; date_in[4] = month_in[1];
    date_out[3] = month_out[0]; date_out[4] = month_out[1];

    return count_day(date_in, date_out);

}

//-------------------------------------
string longestDuration(const string& schedule) {
    string shipnumber, token;
    ifstream input(schedule);

   //------------------------ xu ly shipnumber

   for(int i=1 ; i<=4 ; i++) input >> shipnumber;
   if(shipnumber == "000") return " ";
   for(int i=0 ; i<3 ; i++){
        if(!(shipnumber[i] >= '0' && shipnumber[i]<= '9')) return " ";
    }    

    //------------------------------- xu ly tu dong thu 2 

    shipinfo ship[100];
    int num = stoi(shipnumber);
    
    for(int i=1 ; i<= num ; i++){
    input >> ship[i].name >> ship[i].day_in >> ship[i].time_in >> token >> ship[i].day_out >> ship[i].time_out ;
    ship[i].name.erase(ship[i].name.end() - 1);
    }
 if(invalidTime(schedule) == -1){
        return " ";
    }

    //-------------------
    string date_in, date_out;
    size_t pos1, pos2;
    int day, hour;
    

    for(int i=1 ; i<=num ; i++){
        if( check_date(ship[i].day_in)  == 1 &&
            check_hour(ship[i].time_in) == 1 &&
            check_date(ship[i].day_out) == 1 &&
            check_hour(ship[i].time_out)== 1){
                
                pos1 = ship[i].day_in.find('?');
                pos2 = ship[i].day_out.find('?');

                
                    date_in = ship[i].day_in;
                    date_out = ship[i].day_out;
                    

                if((pos1 != std :: string :: npos) || (pos2 != std :: string :: npos)){
                    day = max_day(date_in, date_out);
                }
                else
                day = count_day(date_in , date_out);

                pos1 = ship[i].time_in.find('?');
                pos2 = ship[i].time_out.find('?');

                if((pos1 != std :: string :: npos) || (pos2 != std :: string :: npos)){
                    hour = max_hour(date_in, ship[i].time_in, date_out, ship[i].time_out);
                }
                else
                {
                    hour = count_hour(date_in , ship[i].time_in , date_out , ship[i].time_out);
                }

                ship[i].time = day*1440 + hour;            
        }
        else
        {
            ship[i].time = -1;
        } cd

        int max = 0;

        for( int i=1 ; i<= num ; i++){
            if(max <= ship[i].time){
                max = ship[i].time;
                ship[i].check_max = true;
            }
            else
            ship[i].check_max = false;
        }

        for(int i=num ; i>0 ; i--){
            if(ship[i].check_max = true)
            return ship[i].name;
        }
    }       
}
    
//--------------------------------------

int solveCrate(int* arr, int size, int k) {
     for (int i = 1; i < k; ++i) {
        for (int j = 0; j < size - i; ++j) {
            arr[j] = arr[j] + arr[j + 1];
        }
    }


    // Tính tổng hàng thứ k
    int sum = 0;
    for (int i = 0; i < size - k + 1; ++i) {
        sum += arr[i];
    }

    // Lấy 3 chữ số cuối cùng của tổng và trả về
    return sum % 1000;
}

//-------------------------------------

struct address {
    int x;
    int y;
};

void go_up(address &vitri){
    if(vitri.x == 0) vitri.x = 9;
    else vitri.x -= 1;
}
void go_down(address &vitri){
    if(vitri.x = 9) vitri.x =0;
    else vitri.x += 1;
}
void turn_left(address &vitri){
    if(vitri.y == 0) vitri.y = 9;
    else vitri.y -= 1;
}
void turn_right(address &vitri){
    if(vitri.y == 9) vitri.y = 0;
    else vitri.y += 1;
}

void back_up(address &vitri){
    if(vitri.x = 9) vitri.x =0;
    else vitri.x += 1;
}
void back_down(address &vitri){
    if(vitri.x == 0) vitri.x = 9;
    else vitri.x -= 1;
}
void return_left(address &vitri){
    if(vitri.y == 9) vitri.y = 0;
    else vitri.y += 1;
}
void return_right(address &vitri){
    if(vitri.y == 0) vitri.y = 9;
    else vitri.y -= 1;
}

//-----

void T_teleport(address &vitri , char (&mapp)[10][10], string &outPath){
    address tele; 

    for(int x=0 ; x<10 ; x++){
        for(int y=0 ; y<10 ; y++){
            if(mapp[x][y] == 'T' && vitri.x != x && vitri.y != y)
            {
                vitri.x = x;
                vitri.y = y;
            }
        }
    }

    outPath += to_string(vitri.x) + ',' + to_string(vitri.y) + ';' ;
}

//-----

void rotate_maze(address &vitri, address &temple, char (&mapp)[10][10]){
    for(int i=0 ; i<10 ; i++){
        for(int j=0 ; j<5 ; j++){
            std :: swap(mapp[9-j][i] , mapp[j][i]);
        }
    }

    for(int i=0 ; i<10 ; i++){
        for(int j=0 ; j<5 ; j++){
            std :: swap(mapp[i][9-j] , mapp[i][j]);
        }
    }    

    for(int x=0 ; x<10 ; x++){     // cap nhat lai gia tri cua temple
        for(int y=0 ; y<10 ; y++){
            if(mapp[x][y] == 'A'){
                temple.x = x;
                temple.y = y;
            }

            if(mapp[x][y] == 'R'){
                vitri.x = x;
                vitri.y = y;
            }
        }
    }
}

//-----

void reverse_moveStyle(string &temp_moveStyle){
    int length = temp_moveStyle.length();
    int start = 0;
    int end = length - 1;

    while (start < end) {
        // Hoán đổi ký tự tại hai chỉ số start và end
        char temp = temp_moveStyle[start];
        temp_moveStyle[start] = temp_moveStyle[end];
        temp_moveStyle[end] = temp;

        // Di chuyển chỉ số start về phía trước và chỉ số end về phía sau
        ++start;
        --end;
    }


}

bool investigateTemple(const string& map, const string& moveStyle, int stamina, int& outTime, string& outPath) {
    
    char mapp[10][10];

    ifstream input(map);

    for(int i=0 ; i < 10 ; i++){
        for(int j=0 ; j < 10 ; j++){
            input >> mapp[i][j];
        }
    }

address vitri, temple;;
address *wall = new address;

int temp = 0;;

for(int x=0 ; x<10 ; x++){       
    for(int y=0 ; y<10 ; y++){
        if(mapp[x][y] == 'S'){  // tim vi tri bat dau cua Holmes
            vitri.x = x;
            vitri.y = y;
        }
        if(mapp[x][y] == 'X'){  // mang luu dia chi cua tuong
            wall[temp].x = x;
            wall[temp].y = y;
            temp++;
        }
        if(mapp[x][y] == 'A'){  //  vi tri cua temple
            temple.x = x;
            temple.y = y;
        }
    }
}

size_t pos = moveStyle.length();
int len = static_cast<int>(pos);

string temp_moveStyle = moveStyle;

while(stamina >0){
    for(int i=0 ; i < len ; i++){
        if(temp_moveStyle[i] == 'U') go_up(vitri);
        else
        if(temp_moveStyle[i] == 'D') go_down(vitri);
        else
        if(temp_moveStyle[i] == 'L') turn_left(vitri);
        else
        if(temp_moveStyle[i] == 'R') turn_right(vitri);

        outTime += 1;
        outPath += to_string(vitri.x) + ',' + to_string(vitri.y) + ';' ;

        if(mapp[vitri.x][vitri.y] == 'X'){    // gặp wall  sẽ đi lui 
        if(temp_moveStyle[i] == 'U') back_up(vitri);
        else
        if(temp_moveStyle[i] == 'D') back_down(vitri);
        else
        if(temp_moveStyle[i] == 'L') return_left(vitri);
        else
        if(temp_moveStyle[i] == 'R') return_right(vitri);

        outTime -= 1;
        for(int i=0 ; i<6 ; i++) outPath.pop_back();
        }

        if(vitri.x == temple.x && vitri.x == temple.y) return true; 

        if(mapp[vitri.x][vitri.y] == 'T'){
            T_teleport(vitri , mapp , outPath);
        }
        else
        if(mapp[vitri.x][vitri.y] == 'C'){
            rotate_maze(vitri, temple , mapp);
        }
        else
        if(mapp[vitri.x][vitri.y] == 'R'){
            reverse_moveStyle(temp_moveStyle);
        }



    }

    
}



}

//-------------------------------------


int readFile(
    const string & filename,
    string & schedule,
    string & map,
    string & moveStyle,
    int & stamina,
    int & size,
    int & k,
    int* arr
) {
//This function is used to read the input file,
//DO NOT MODIFY THIS FUNCTION
    ifstream myFile(filename);
    if (myFile.is_open()) {
        myFile >> schedule
               >> map
               >> moveStyle
               >> stamina
               >> size
               >> k;
        for(int i = 0; i < size; i++){
            myFile >> arr[i];
        }
        return 1;
    }
    else return 0;
}

int main() {
    string filename = "input1.txt";
    string schedule, map, moveStyle;
    int stamina, size, k;
    int arr[50];

    bool isRead = readFile(filename, schedule, map, moveStyle,
                           stamina, size, k, arr);
    if (isRead){
        cout << schedule << endl;
        cout << map << endl;
        cout << moveStyle << endl;
        cout << stamina << endl;
        cout << size << endl;
        cout << k << endl;
        for(int i = 0; i < size; i++){
            cout << arr[i];
            if(i == size - 1) cout << endl;
            else cout << " ";
        }

        // The first case
        
        int numInvalid = invalidTime(schedule);
        string longestDurationShip = longestDuration(schedule);
        cout << "numInvalid: " << numInvalid << endl;
        cout << "longestDurationShip: " << longestDurationShip << endl;

        // The second case
        int outTime;
        string outPath;

        bool foundAltar = investigateTemple(map, moveStyle, stamina, outTime, outPath);
        cout << "Found altar: " << foundAltar << endl;
        cout << "outTime: " << outTime << endl;
        cout << "outPath: " << outPath << endl;

        // Task 3
        int password = solveCrate(arr, size, k);
        cout << password << endl;
    }
    else{
        cout << "Cannot read input file";
    }
    return 0;

}

