import re
import string

#*******************************************************************************************************
#                          STRINGS AND REGULAR EXPRESSION LISTS                                        #
#*******************************************************************************************************
relativeDays = "(today|yesterday|tomorrow|tonight|tonite)"
compareStr = "(before|after|earlier|later|ago|from now)"
compare2Str = "(this|next|last|for last|for the last|for the past|for past)"
exprStr = "(an|a|this)"
specificStr = "(within|by)"
timeZoneStr = "(in morning|in the morning|in the evening|in evening|at noon)"
year = "((?<=\s)\d{4}|^\d{4})"
numbers = "(^a(?=\s)|one|two|three|four|five|six|seven|eight|nine|ten|eleven|twelve|thirteen|fourteen|fifteen|sixteen|seventeen|eighteen|nineteen|twenty|thirty|forty|fifty|sixty|seventy|eighty|ninety|hundred|thousand)"
day = "(monday|tuesday|wednesday|thursday|friday|saturday|sunday)"
weekDays = "(monday|tuesday|wednesday|thursday|friday|saturday|sunday)"
month = "(january|february|march|april|may|june|july|august|september|october|november|december)"
dmy = "(year|day|week|month|hour|minute)"


regxp1 = "((\d+|(" + numbers + "[-\s]?)+) " + dmy + "s? " + compareStr + ")"
regxp2 = "(" + compare2Str + " (" + dmy + "|" + weekDays + "|" + month + "))"
regxp3 = "((\d+|(" + compare2Str + "[-\s]?)+) " + numbers + "s? " + dmy + ")"
regxp4 = "("+"("+specificStr+"[-\s]?)"+"("+exprStr+"[-\s]?)"+"("+dmy+"[-\s]?)"+")"
regxp5 = "("+"("+compare2Str+"[-\s]?)"+"("+numbers+"[-\s]?)"+"("+dmy+"[-\s]?)"+")"
regxp6 = "("+"("+compareStr+"[-\s]?)"+"("+numbers+"[-\s]?)"+")"
regxp7 = "("+"("+compareStr+"[-\s]?)"+"(\d)+"+")"
regxp8 = "((\d+|(" + numbers + "[-\s]?)+) " + timeZoneStr + ")"


reg1 = re.compile(regxp1, re.IGNORECASE)
reg2 = re.compile(relativeDays, re.IGNORECASE)
reg3 = re.compile(regxp2, re.IGNORECASE)
reg4 = re.compile(regxp4, re.IGNORECASE)
reg5 = re.compile(regxp5, re.IGNORECASE)
reg6 = re.compile(regxp6, re.IGNORECASE)
reg7 = re.compile(regxp7, re.IGNORECASE)
reg8 = re.compile(regxp8, re.IGNORECASE)


#*******************************************************************************************************
#                                            HASH FUNSTIONS                                            #
#*******************************************************************************************************
                                            
HashWeek = {
    'Sunday': 1,
    'Monday': 2,
    'Tuesday': 3,
    'Wednesday': 4,
    'Thursday': 5,
    'Friday': 6,
    'Saturday': 7}


HashMonths = {
    'January': 1,
    'February': 2,
    'March': 3,
    'April': 4,
    'May': 5,
    'June': 6,
    'July': 7,
    'August': 8,
    'September': 9,
    'October': 10,
    'November': 11,
    'December': 12}

def HashNumber(number):
    if re.match(r'one|^a\b', number, re.IGNORECASE):
        return 1
    if re.match(r'two', number, re.IGNORECASE):
        return 2
    if re.match(r'three', number, re.IGNORECASE):
        return 3
    if re.match(r'four', number, re.IGNORECASE):
        return 4
    if re.match(r'five', number, re.IGNORECASE):
        return 5
    if re.match(r'six', number, re.IGNORECASE):
        return 6
    if re.match(r'seven', number, re.IGNORECASE):
        return 7
    if re.match(r'eight', number, re.IGNORECASE):
        return 8
    if re.match(r'nine', number, re.IGNORECASE):
        return 9
    if re.match(r'ten', number, re.IGNORECASE):
        return 10
    if re.match(r'eleven', number, re.IGNORECASE):
        return 11
    if re.match(r'twelve', number, re.IGNORECASE):
        return 12
    if re.match(r'thirteen', number, re.IGNORECASE):
        return 13
    if re.match(r'fourteen', number, re.IGNORECASE):
        return 14
    if re.match(r'fifteen', number, re.IGNORECASE):
        return 15
    if re.match(r'sixteen', number, re.IGNORECASE):
        return 16
    if re.match(r'seventeen', number, re.IGNORECASE):
        return 17
    if re.match(r'eighteen', number, re.IGNORECASE):
        return 18
    if re.match(r'nineteen', number, re.IGNORECASE):
        return 19
    if re.match(r'twenty', number, re.IGNORECASE):
        return 20
    if re.match(r'thirty', number, re.IGNORECASE):
        return 30
    if re.match(r'forty', number, re.IGNORECASE):
        return 40
    if re.match(r'fifty', number, re.IGNORECASE):
        return 50
    if re.match(r'sixty', number, re.IGNORECASE):
        return 60
    if re.match(r'seventy', number, re.IGNORECASE):
        return 70
    if re.match(r'eighty', number, re.IGNORECASE):
        return 80
    if re.match(r'ninety', number, re.IGNORECASE):
        return 90
    if re.match(r'hundred', number, re.IGNORECASE):
        return 100
    if re.match(r'thousand', number, re.IGNORECASE):
      return 1000
      

#*******************************************************************************************************
#                    SEARCH FOR SPECIFIC GRAMMER AND MARK IN TEXT                                     #
#*******************************************************************************************************
def SearchRegExp(data_):

    # Initialization
    expList = []
    expList1 = []
    expList2 = []
    expList3 = []

    # re.findall() finds all the substring matches, keep only the full
    # matching string. Captures expressions such as 'number of days' ago, etc.
    found = reg1.findall(data_)
    found = [a[0] for a in found if len(a) > 1]
    for dt in found:
        expList.append(dt)

    found = reg3.findall(data_)
    found = [a[0] for a in found if len(a) > 1]
    for dt in found:
        expList.append(dt)

    found = reg4.findall(data_)
    found = [a[0] for a in found if len(a) > 1]
    for dt in found:
        expList.append(dt)

    found = reg5.findall(data_)
    found = [a[0] for a in found if len(a) > 1]
    for dt in found:
        expList.append(dt)

    found = reg6.findall(data_)
    found = [a[0] for a in found if len(a) > 1]
    for dt in found:
        expList1.append(dt)

    found = reg7.findall(data_)
    found = [a[0] for a in found if len(a) > 1]
    for dt in found:
        expList2.append(dt)

    found = reg8.findall(data_)
    found = [a[0] for a in found if len(a) > 1]
    for dt in found:
        expList3.append(dt)
        
    found = reg2.findall(data_)
    for dt in found:
        expList.append(dt)
        
    for dt in expList:
        data_ = re.sub(dt + '(?!</RE1>)', '<RE1>' + dt + '</RE1>', data_)
        
    for dt in expList1:
        data_ = re.sub(dt + '(?!</RE2>)', '<RE2>' + dt + '</RE2>', data_)
        
    for dt in expList2:
        data_ = re.sub(dt + '(?!</RE3>)', '<RE3>' + dt + '</RE3>', data_)
        
    for dt in expList3:
        data_ = re.sub(dt + '(?!</RE4>)', '<RE4>' + dt + '</RE4>', data_)

    return data_

#*******************************************************************************************************
#                           EXTRACT DATA FROM MARKED TEXT                                             #
#*******************************************************************************************************
def ExtractDateAndTime(markedStr_, currentDate_):

    # Find all identified dt and put them into a list
    dt_regex = re.compile(r'<RE1>.*?</RE1>', re.DOTALL)
    expList = dt_regex.findall(markedStr_)
    expList = map(lambda dt:re.sub(r'</?RE1.*?>', '', dt), \
                expList)
    dt_add = 'DEFAULT'
    
    for dt in expList:
        ret_val = 'DEFAULT' 

        dt_ori = dt  
        if re.search(numbers, dt, re.IGNORECASE):
            split_dt = re.split(r'\s(?=days?|months?|years?|weeks?|hours?|minutes?)', \
                                                              dt, re.IGNORECASE)
            value = split_dt[0]
            unit = split_dt[1]
            num_list = map(lambda s:HashNumber(s),re.findall(numbers + '+', \
                                          value, re.IGNORECASE))
            dt = `sum(num_list)` + ' ' + unit           
            
        #Last ** year-month or day            
        if re.search('for last', markedStr_) or re.search('for the last', markedStr_) or re.search('for past', markedStr_) or re.search('for the past', markedStr_):
            bd = currentDate_;
            if re.search('year', dt):
                difference = int(re.split(r'\s', dt)[0])
                ret_val = 'Start'+str(currentDate_.year-difference)+'year-End'+str(currentDate_.year)+'year'
            if re.search('month', dt):
                difference = int(re.split(r'\s', dt)[0])
                ret_val = 'Start'+str(currentDate_.month-difference)+'-End'+str(currentDate_)
            if re.search('day', dt):
                difference = int(re.split(r'\s', dt)[0])
                ret_val = 'Start'+str(currentDate_.year)+'-'+str(currentDate_.month)+'-'+str(currentDate_.day-difference)+'-End-'+str(currentDate_)
            if re.search('hour', dt):
                difference = int(re.split(r'\s', dt)[0])
                ret_val = 'Start'+str(currentDate_.hour-difference)+'hour-'+str(currentDate_.minute)+'minute-End'+str(currentDate_.hour)+'hour-'+str(currentDate_.minute)+'minute';
            if re.search('minute', dt):
                difference = int(re.split(r'\s', dt)[0])
                ret_val = 'Start'+str(currentDate_.hour)+'hour-'+str(currentDate_.minute-difference)+'minute-End'+str(currentDate_.hour)+'hour-'+str(currentDate_.minute)+'minute';

        # Specific dates
        elif re.match(r'\d{4}', dt):
            ret_val = str(dt)

        elif re.match(r'tonight|tonite|today', dt, re.IGNORECASE):
            ret_val = str(currentDate_)+'day'
        elif re.match(r'yesterday', dt, re.IGNORECASE):
            ret_val = str(currentDate_.day-1)+'day'
        elif re.match(r'tomorrow', dt, re.IGNORECASE):
            ret_val = str(currentDate_.day+1)+'day'

        elif re.match(r'last ' + weekDays, dt, re.IGNORECASE):
            day = 7-HashWeek[dt.split()[1]]
            ret_val = str(currentDate_.day-1 -day -int(currentDate_.toordinal()%7))

        elif re.match(r'this ' + weekDays, dt, re.IGNORECASE):
            day = HashWeek[dt.split()[1]]
            ret_val = str(currentDate_.day +day -int(currentDate_.toordinal()%7) -1)

        elif re.match(r'next ' + weekDays, dt, re.IGNORECASE):
            day = HashWeek[dt.split()[1]]
            ret_val = str(currentDate_.day +day -int(currentDate_.toordinal()%7) +6)

        elif re.match(r'last month', dt, re.IGNORECASE):
            if (currentDate_.month-1 <1):
                 currentDate_.year=currentDate_.year-1
                 currentDate_.month = 12
                 ret_val = str(currentDate_.month) + '-' + str(currentDate_.year) 
            else:
                 ret_val = str(currentDate_.month - 1) + '-' + str(currentDate_.year) 

        elif re.match(r'this month', dt, re.IGNORECASE):
            ret_val = str(currentDate_.month)

        elif re.match(r'next month', dt, re.IGNORECASE):
            if (currentDate_.month+1 >12):
                 currentDate_.year=currentDate_.year+1
                 currentDate_.month = currentDate_.month%12
                 ret_val = str(currentDate_.month) + '-' + str(currentDate_.year) 
            else:
                 ret_val = str(currentDate_.month + 1) + '-' + str(currentDate_.year) 
        elif re.match(r'last month', dt, re.IGNORECASE):
            if currentDate_.month == 1:
                ret_val = str(currentDate_.year - 1) + '-' + '12'
            else:
                ret_val = str(currentDate_.year) + '-' + str(currentDate_.month - 1)
        elif re.match(r'this month', dt, re.IGNORECASE):
                ret_val = str(currentDate_.year) + '-' + str(currentDate_.month)
        elif re.match(r'next month', dt, re.IGNORECASE):
            if currentDate_.month == 12:
                ret_val = str(currentDate_.year + 1) + '-' + '1'
            else:
                ret_val = str(currentDate_.year) + '-' + str(currentDate_.month + 1)
        elif re.match(r'last year', dt, re.IGNORECASE):
            ret_val = str(currentDate_.year - 1)
        elif re.match(r'this year', dt, re.IGNORECASE):
            ret_val = str(currentDate_.year)
        elif re.match(r'next year', dt, re.IGNORECASE):
            ret_val = str(currentDate_.year + 1)
        elif re.match(r'this hour', dt, re.IGNORECASE):
            ret_val = str(currentDate_.hour)
        elif re.match(r'last hour', dt, re.IGNORECASE):
            if currentDate_.month == 1:
                ret_val = 'day' + str(currentDate_.day-1);
                ret_val = '24 hour'
            else:
                ret_val = str(currentDate_.hour-1)
        elif re.match(r'next hour', dt, re.IGNORECASE):
            if currentDate_.month == 24:
                ret_val = 'day' + str(currentDate_.day+1);
                ret_val = '0 hour'
            else:
                ret_val = str(currentDate_.hour+1)
        elif re.match(r'\d+ days? (ago|earlier|before)', dt, re.IGNORECASE):
            difference = int(re.split(r'\s', dt)[0])
            ret_val = str(currentDate_.day-difference)
        elif re.match(r'\d+ days? (later|after|from now)', dt, re.IGNORECASE):
            difference = int(re.split(r'\s', dt)[0])
            ret_val = str(currentDate_.day+difference)
        elif re.match(r'\d+ hours? (ago|earlier|before)', dt, re.IGNORECASE):
            difference = int(re.split(r'\s', dt)[0])
            ret_val = str(currentDate_.hour-difference)
        elif re.match(r'\d+ hours? (later|after|from now)', dt, re.IGNORECASE):
            difference = int(re.split(r'\s', dt)[0])
            ret_val = str(currentDate_.hour+difference)
        elif re.match(r'\d+ months? (ago|earlier|before)', dt, re.IGNORECASE):
            extra = 0
            difference = int(re.split(r'\s', dt)[0])

            if (currentDate_.month - difference % 12) < 1:
                extra = 1

            year = str(currentDate_.year - difference // 12 - extra)
            month = str((currentDate_.month - difference % 12) % 12)

            if month == '0':
                month = '12'
            ret_val = year + '-' + month
        elif re.match(r'\d+ months? (later|after|from now)', dt, re.IGNORECASE):
            extra = 0
            difference = int(re.split(r'\s', dt)[0])
            if (currentDate_.month + difference % 12) > 12:
                extra = 1
            year = str(currentDate_.year + difference // 12 + extra)
            month = str((currentDate_.month + difference % 12) % 12)
            if month == '0':
                month = '12'
            ret_val = year + '-' + month
        elif re.match(r'\d+ years? (ago|earlier|before)', dt, re.IGNORECASE):
            difference = int(re.split(r'\s', dt)[0])
            ret_val = str(currentDate_.year - difference)
        elif re.match(r'\d+ years? (later|after|from now)', dt, re.IGNORECASE):
            difference = int(re.split(r'\s', dt)[0])
            ret_val = str(currentDate_.year + difference)
        elif re.match(r'\d+ minutes? (later|after|from now)', dt, re.IGNORECASE):
            difference = int(re.split(r'\s', dt)[0])
            if currentDate_.minute+difference > 59:
                ret_val = str(currentDate_.hour+1)+'h'+str((currentDate_.minute+difference)%60)+'m'
            else:
                ret_val = str(currentDate_.hour)+'h'+str(currentDate_.minute+difference)+'m'          
            
        elif re.match(r'by this year', dt, re.IGNORECASE):
            ret_val = str(currentDate_.year)
        elif re.match(r'by next year', dt, re.IGNORECASE):
            ret_val = str(currentDate_.year + 1)
        elif re.match(r'by an hour', dt, re.IGNORECASE):
            ret_val = str(currentDate_.hour)
        elif re.match(r'within an hour', dt, re.IGNORECASE):
            ret_val = "Start-" +str(currentDate_.hour) +'h'+str(currentDate_.minute)+ 'm-End' +str(currentDate_.hour+1) +'h'+str(currentDate_.minute)+ 'm';
        elif re.match(r'by last hour', dt, re.IGNORECASE):
            if currentDate_.month == 1:
                ret_val = 'day' + str(currentDate_.day-1);
                ret_val = '24 hour'
            else:
                ret_val = str(currentDate_.hour-1)
        elif re.match(r'within an hour', dt, re.IGNORECASE):
            if currentDate_.month == 24:
                ret_val = 'day' + str(currentDate_.day+1);
                ret_val = '0 hour'
            else:
                ret_val = str(currentDate_.hour+1)

        if(ret_val!='DEFAULT'):
            dt_add+=ret_val
            
    dt_regex11 = re.compile(r'<RE2>.*?</RE2>', re.DOTALL)
    expList1 = dt_regex11.findall(markedStr_)
    expList1 = map(lambda dt:re.sub(r'</?RE2.*?>', '', dt), \
                expList1)

    for dt in expList1:
        ret_val = 'DEFAULT' 
        dt_ori11 = dt   
        if re.search(numbers, dt, re.IGNORECASE):
            split_dt11 = re.split(r'\s(?=days?|months?|years?|weeks?|hours?|minutes?)', \
                                                              dt, re.IGNORECASE)
            value11 = split_dt11[0]
            num_list11 = map(lambda s:HashNumber(s),re.findall(numbers + '+', \
                                          value11, re.IGNORECASE))
            dt = `sum(num_list11)`   
            if((int(dt))<(int(currentDate_.hour))):
                t1=(currentDate_.day+1)
                ret_val=str(t1)+'day-'+str(dt)+'hours'
            else:
                ret_val=str(currentDate_.day)+'day-'+str(dt)+'hours'
                
        if(ret_val!='DEFAULT'):
            dt_add+=ret_val
            
    dt_regex12 = re.compile(r'<RE3>.*?</RE3>', re.DOTALL)
    expList2 = dt_regex12.findall(markedStr_)
    expList2 = map(lambda dt:re.sub(r'</?RE3.*?>', '', dt), \
                expList2)
                
    for dt in expList2:
        ret_val = 'DEFAULT' 
        dt_ori12 = dt   
        difference = int(re.split(r'\s', dt)[1])
        if((int(difference))<(int(currentDate_.hour))):
            t1=int(currentDate_.day)
            if re.search('before',markedStr_)or re.search('Before',markedStr_):
                ret_val='Start'+str(int(currentDate_.day))+'day'+str(int(currentDate_.hour))+'hours-End'+str(int(t1+1))+'day-'+str(int(difference))+'hours'
            else:                
                ret_val='Start'+str(int(t1+1))+'day-'+str(int(difference))+'hours'
        else:
            ret_val=str(currentDate_.day)+'day-'+str(int(difference))+'hours'
                
        if(ret_val!='DEFAULT'):
            dt_add+=ret_val
            
    dt_regex14 = re.compile(r'<RE4>.*?</RE4>', re.DOTALL)
    expList3 = dt_regex14.findall(markedStr_)
    expList3 = map(lambda dt:re.sub(r'</?RE4.*?>', '', dt), \
                expList3)
    for dt in expList3:
        ret_val = 'DEFAULT' 
        dt_ori14 = dt
        split_dt14 = re.split(r'\s(?=days?|months?|years?|weeks?|hours?|minutes?)', \
                                                          dt, re.IGNORECASE)
        value14 = split_dt14[0]
        num_list14 = map(lambda s:HashNumber(s),re.findall(numbers + '+', \
                                      value14, re.IGNORECASE))
        val = `sum(num_list14)`           
        val=int(val)
        if re.search('in the evening',markedStr_) or re.search('in evening',markedStr_):
            ret_val=str(int(val+12))+'hours'            
        else:
            ret_val=str(val)+'hours'            
                
        if(ret_val!='DEFAULT'):
            dt_add+=ret_val
        markedStr_ = re.sub('before','',dt_add)
        markedStr_ = re.sub('after','',dt_add)
         
    markedStr_ = re.sub('DEFAULT','',dt_add)
    return markedStr_

#*******************************************************************************************************
#                                        MAIN FUNCTION                                                 #
#*******************************************************************************************************
if __name__ == '__main__':
    from datetime import datetime
    currentDate_ = datetime.now() 
    data=raw_input("Enter string: ")
    t1= SearchRegExp(data)
    print ExtractDateAndTime(t1,currentDate_)
