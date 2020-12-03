
import 'dart:io';

import 'package:training_workout/main.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_datetime_picker/flutter_datetime_picker.dart';
//import 'package:flutter_local_notifications/flutter_local_notifications.dart';
import 'package:numberpicker/numberpicker.dart';
import 'package:url_launcher/url_launcher.dart';
import 'package:path_provider/path_provider.dart';
import 'package:provider/provider.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:after_init/after_init.dart';
import 'package:flutter_phoenix/flutter_phoenix.dart';
import 'package:webview_flutter/webview_flutter.dart';
import 'package:android_alarm_manager/android_alarm_manager.dart';
import 'data.dart';
import 'localization.dart';
import 'main.dart';
class SettingsButton extends StatelessWidget{
  String name;
  Function onclick;
  Icon icon;
  SettingsButton(this.name,this.onclick,this.icon);
  @override
  Widget build(BuildContext context) {
    return FlatButton(
      onPressed: onclick,
      child: Padding(
        padding: const EdgeInsets.all(12.0),
        child: Row(
          children: <Widget>[
            Padding(
              padding: const EdgeInsets.all(4.0),
              child: icon,
            ),
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: Text(name,style: TextStyle(fontSize: 16),),
            ),
          ],
        ),
      ),
    );
  }

}
class MyProfile extends StatefulWidget{


  @override
  createState()=> new _MyProfileState();
}
class _MyProfileState extends State<MyProfile> with AfterInitMixin<MyProfile>{

  int weight,height,heightI,heightF;
  String heightM='cm', measureW ='kg';
  String date="";
  SharedPreferences pref;
  getW() {

    setState(() {
      weight = pref.getInt("weight")??50;
      measureW=pref.getString("measureW")??"kg";

    });
  }
  getD(){
    setState(() {
      date=pref.getString("date");
    });
  }
  setW() {
    pref.setInt("weight",weight);
    pref.setString("measureW", measureW);
  }
  @override
  void didInitState() {
    pref=Provider.of<Data>(context).prefs;
    getH();
    getW();
  }


  getH() {

    var a=pref.getString("measureH")??'cm';
    setState(() {
      height = pref.getInt("height") ?? 150;
      heightF=pref.getInt("feet")??5;
      heightI=pref.getInt("inch")??0;
    });
    if (a=='cm') {
      setState(() {
        heightM='cm';
      });
    }
    else{
      setState(() {
        heightM='f/in';
      });
    }
  }
  setH() async{

    pref.setInt("height",height);
    pref.setString("measureH", "cm");
  }
  setHF() async{
    pref.setInt("feet",heightF);
    pref.setString("measureH", "f/in");
  }
  setHI() async{
    pref.setInt("inch",heightI);
  }
//  getHeight(BuildContext context){
//    showDialog(
//        context: context,
//        builder: (BuildContext context) {
//          // return object of type Dialog
//          return AlertDialog(
//            title: new Text(AppLocalizations.of(context).translate("urh8")),
//            content: HeightPicker(),
//            actions: <Widget>[
//              // usually buttons at the bottom of the dialog
//              new FlatButton(
//                child: new Text(AppLocalizations.of(context).translate("sbmt")),
//                onPressed: () {
//                  getH();
//                  Navigator.of(context).pop();
//                },
//              ),
//            ],
//          );
//        });
//  }
  getHeight(BuildContext context){
    showModalBottomSheet(
        context: context,
        shape: RoundedRectangleBorder(borderRadius: BorderRadius.only(topRight: Radius.circular(18),topLeft: Radius.circular(18))),
        builder: (BuildContext context) {
          // return object of type Dialog

          return    Container(
            height: 255,
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: <Widget>[
                Padding(
                  padding: const EdgeInsets.all(10.0),
                  child: Text(AppLocalizations.of(context).translate("urh8"),style: TextStyle(fontSize: 20,fontWeight: FontWeight.bold),),
                ),
                HeightPicker(),
                Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly,crossAxisAlignment: CrossAxisAlignment.end,children: <Widget>[
                  SizedBox(
                    width: MediaQuery.of(context).size.width/2-50,
                    child: new OutlineButton(child: new Text(AppLocalizations.of(context).translate("cancel")),color: Colors.white,onPressed: (){if(heightM=='cm'){setH();}else{setHF();setHI();};
                    Navigator.of(context).pop();},textColor: Colors.black,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0),)),
                  ),
                  SizedBox(
                    width: MediaQuery.of(context).size.width/2-50,
                    child: new FlatButton(child: new Text(AppLocalizations.of(context).translate("sbmt")),color: Color.fromARGB(255,207,78,61),
                        onPressed: (){getH();
                        Navigator.of(context).pop();},textColor: Colors.white,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0))),
                  ),

                ],)
              ],
            ),
          );
        });
  }
  getWeight(BuildContext context){
    showModalBottomSheet(
        context: context,
        shape: RoundedRectangleBorder(borderRadius: BorderRadius.only(topRight: Radius.circular(18),topLeft: Radius.circular(18))),
        builder: (BuildContext context) {
          // return object of type Dialog

            return    Container(
              height: 255,
              child: Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: <Widget>[
                            Padding(
                              padding: const EdgeInsets.all(10.0),
                              child: Text(AppLocalizations.of(context).translate("urw8"),style: TextStyle(fontSize: 20,fontWeight: FontWeight.bold),),
                            ),
                            WeightPicker(isgoal: false,),
                          Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly,crossAxisAlignment: CrossAxisAlignment.end,children: <Widget>[
                            SizedBox(
                              width: MediaQuery.of(context).size.width/2-50,
                              child: new OutlineButton(child: new Text(AppLocalizations.of(context).translate("cancel")),color: Colors.white,onPressed: (){setW();
                              Navigator.of(context).pop();},textColor: Colors.black,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0),)),
                            ),
                            SizedBox(
                              width: MediaQuery.of(context).size.width/2-50,
                              child: new FlatButton(child: new Text(AppLocalizations.of(context).translate("sbmt")),color: Color.fromARGB(255,207,78,61),
                                  onPressed: (){getW();
                              Navigator.of(context).pop();},textColor: Colors.white,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0))),
                            ),

                          ],)
                          ],
                      ),
            );
    });
  }


  getDate(BuildContext context){
    showModalBottomSheet(
        context: context,
        shape: RoundedRectangleBorder(borderRadius: BorderRadius.only(topRight: Radius.circular(18),topLeft: Radius.circular(18))),
        builder: (BuildContext context) {
          int monthbirth=1;
          int day=1;
          int year=1920;
          return StatefulBuilder(builder: (context,setState){
          // return object of type Dialog
          List<int> ch=new List();
          List<int> ch1=[31,year%4==0&&year%100!=0?29:28,31,30,31,30,31,31, 30,31,30,31];
          List<int> ch2=new List();
          List<int> ch3=new List();

          for (int i=1;i<=31;i++){
            if (i<13)
              ch2.add(i);
            ch.add(i);
          }
          for (int i=1920;i<DateTime.now().year-8;i++){
            ch3.add(i);
          }
          FixedExtentScrollController scr=FixedExtentScrollController(initialItem: 0);
          //print(year);
          return    Container(
              height: 300,
            width: MediaQuery.of(context).size.width,
            child: Column(mainAxisAlignment: MainAxisAlignment.spaceBetween,crossAxisAlignment: CrossAxisAlignment.start,
              children: <Widget>[
                Padding(
                  padding: const EdgeInsets.all(15.0),
                  child: Text(AppLocalizations.of(context).translate("birth"),textAlign: TextAlign.left,style: TextStyle(fontWeight: FontWeight.bold,fontSize: 20),),
                ),
                Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly,children: <Widget>[
                  Container(width: 50,height:170,child: CupertinoPicker(highlighterBorderWidth: 2.5,highlighterBorder: Color.fromARGB(255, 207, 78, 61),scrollController:scr,itemExtent: 45,children: ch.sublist(0,ch1[monthbirth-1]).map((e) => Center(child: Text(e.toString()))).toList(),onSelectedItemChanged: (item){
                    setState((){day=item+1;});
                  },)),
                  Container(width: 50,height:170,child: CupertinoPicker(highlighterBorderWidth: 2.5,highlighterBorder: Color.fromARGB(255, 207, 78, 61),itemExtent: 45,children: ch2.map((e) => Center(child: Text(e.toString()))).toList(),onSelectedItemChanged: (item)async{setState(() {
                    monthbirth=item+1;

                  });
                  //scr.animateToItem(day-2,duration: Duration(milliseconds: 1000),curve: Curves.easeIn);
                  if (day>26){
                    scr.jumpToItem(day);
                    scr.animateToItem(
                        day-2,
                        duration: Duration(microseconds: 1),
                        curve: Curves.easeIn);
                  }
                  },)),
                    Container(width:50,height:170,child: CupertinoPicker(highlighterBorderWidth: 2.5,highlighterBorder: Color.fromARGB(255, 207, 78, 61),itemExtent: 45,children: ch3.map((e) => Center(child: Text(e.toString()))).toList(),onSelectedItemChanged: (item){setState((){year=item+1920;});scr.jumpToItem(day-2);
                    scr.animateToItem(day>ch1[monthbirth-1]?ch1[monthbirth]-1:day,duration: Duration(microseconds: 1),curve: Curves.easeIn);
                    },))
                  ],),
                Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly,crossAxisAlignment: CrossAxisAlignment.end,children: <Widget>[
                  SizedBox(
                    width: MediaQuery.of(context).size.width/2-50,
                    child: new OutlineButton(child: new Text(AppLocalizations.of(context).translate("cancel")),color: Colors.white,onPressed: (){setW();
                    Navigator.of(context).pop();},textColor: Colors.black,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0),)),
                  ),
                  SizedBox(
                    width: MediaQuery.of(context).size.width/2-50,
                    child: new FlatButton(child: new Text(AppLocalizations.of(context).translate("sbmt")),color: Color.fromARGB(255,207,78,61),
                        onPressed: (){pref.setString("date", (day<10?"0":'')+(day).toString()+":"+((monthbirth<10)?"0":'')+(monthbirth).toString()+':'+year.toString());
                        getD();
                        Navigator.of(context).pop();},textColor: Colors.white,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0))),
                  ),

                ],)
              ],
            ),
          );
        });
        }
      );
  }
 //DateTime t=DateTime.now().subtract(Duration(days: 5000));
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(backgroundColor: Color.fromARGB(100, 200, 200, 200),title: Text(AppLocalizations.of(context).translate('myprofile')),textTheme:TextTheme(title: TextStyle(color: Colors.black,fontSize: 20)),iconTheme: IconThemeData(color: Color.fromARGB(255, 100, 100, 100)),),

      body: Container(
          color: Color.fromARGB(100, 200, 200, 200),
          child:
          Column(
            children: <Widget>[Center(
              child: Container(
                //decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.all(Radius.circular(30))),
                //margin: EdgeInsets.only(top:30),
                width: MediaQuery.of(context).size.width,
                color: Colors.white,
                child: InkWell(

                    onTap: () {getWeight(context);},
                    child: Row(

                      children: <Widget>[
                        Padding(
                          padding: const EdgeInsets.all(14.0),
                          child: Text(AppLocalizations.of(context).translate("w8")),
                        ),
                        Spacer(),
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: Text(weight.toString()+' '+AppLocalizations.of(context).translate(measureW)),
                        ),
                      ],

                  ),
                ),
              ),
            ),Container(
              height: 1,color: Colors.grey.shade200,),
              Center(
              child: Container(
                //decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.all(Radius.circular(30))),
                width: MediaQuery.of(context).size.width,
                color: Colors.white,
                child:  InkWell(
                    borderRadius: BorderRadius.all(Radius.circular(30)),
                    onTap: (){getHeight(context);},
                    child: Row(

                      children: <Widget>[
                        Padding(
                          padding: const EdgeInsets.all(14.0),
                          child: Text(AppLocalizations.of(context).translate("h8")),
                        ),
                        Spacer(),
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: Text(heightM=='cm'?height.toString()+' '+AppLocalizations.of(context).translate("cm"):heightF.toString()+AppLocalizations.of(context).translate("ft")+' '+heightI.toString()+AppLocalizations.of(context).translate("in")),
                        ),
                      ],

                  ),
                ),
              ),
            ),
    Container(
    height: 1,color: Colors.grey.shade200,),
    Center(
    child: Container(
    //decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.all(Radius.circular(30))),
    width: MediaQuery.of(context).size.width,
    color: Colors.white,
    child:  InkWell(
    borderRadius: BorderRadius.all(Radius.circular(30)),
    onTap: (){getDate(context);},
    child: Row(

    children: <Widget>[
    Padding(
    padding: const EdgeInsets.all(14.0),
    child: Text(AppLocalizations.of(context).translate("birth")),
    ),
    Spacer(),
    Padding(
    padding: const EdgeInsets.all(8.0),
    child: Text(date),
    ),
    ],

    ),
    ),
    ),
    )],
          )

      ),
    );
  }

}
class LanguageChange extends StatelessWidget{
  // AppLanguage appLanguage;
  //LanguageChange({this.appLanguage});
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(backgroundColor:Color.fromARGB(100, 200, 200, 200),title: Text(AppLocalizations.of(context).translate('lng')),textTheme:TextTheme(title: TextStyle(color: Colors.black,fontSize: 20)),iconTheme: IconThemeData(color: Color.fromARGB(255, 100, 100, 100)),),

        body: Container(

          child:RadioLang(/*appLanguage: appLanguage*/),
        )
    );
  }

}


class WeightPicker extends StatefulWidget{
  bool isgoal;
  WeightPicker({this.isgoal});
  @override
  createState()=>new _WeightPickerState( isgoal: isgoal);
}
class HeightPicker extends StatefulWidget{
  @override
  createState()=>new _HeightPickerState();
}

class MyPicker extends StatelessWidget {
  final int init;
  final onchange;
  MyPicker( this.init,this.onchange);
  @override
  Widget build(BuildContext context) {
    return NumberPicker.integer(highlightSelectedValue:true,initialValue: init, minValue: 66, maxValue: 333, onChanged: onchange);//(newValue)=>setW(newValue,measureW))),
  }
}

class _WeightPickerState extends State<WeightPicker> with AfterInitMixin<WeightPicker>{
  String measureW;
  bool isgoal;
  int weight,goal;
  SharedPreferences pref;
  _WeightPickerState({this.isgoal});
  @override
  void didInitState(){
    pref=pref=Provider.of<Data>(context).prefs;
    getW();
  }
  getW() async{
    setState(() {
      goal=pref.getInt("toweight")??-1;
      weight = pref.getInt("weight")??50;
      measureW=pref.getString("measureW")??"kg";
    });
  }
  setW(int w,String m) async{

//    setState(() {
//      isgoal?goal=w:weight=w;
//      measureW=m;
//    });
    if (isgoal){pref.setInt("toweight", w);}else{
    pref.setInt("weight",w);
    }
    pref.setString("measureW", m);
    getW();
  }
  int init;
  @override
  Widget build(BuildContext context) {
    //pref.setInt("weight", 100);
    //pref.setInt("toweight", 100);
     init=isgoal?(goal==-1?weight:goal):weight;
    return Row(
      //crossAxisAlignment: CrossAxisAlignment.center,
      mainAxisAlignment: isgoal?MainAxisAlignment.center:MainAxisAlignment.spaceAround,
      children: <Widget>[
        Stack(children: [Theme(
            data: Theme.of(context).copyWith(
            accentColor: Colors.black,
    ),
            child: measureW=='kg'?new NumberPicker.integer(highlightSelectedValue:true,initialValue: init, minValue: 30, maxValue: 150, onChanged: (newValue)=>setW(newValue,measureW))
                :new MyPicker(init,(newValue)=>setW(newValue,measureW))),
        Positioned(top: 58,left: 35,child: Container(height: 2,width: 30,color: Color.fromARGB(255,207,78,61),)),
        Positioned(top: 88,left: 35,child: Container(height: 2,width: 30,color: Color.fromARGB(255,207,78,61),))]),

        isgoal?Text(""):DropdownButton<String>(value: measureW,iconSize: 24,elevation: 16,
          underline: Container(
            height: 2,
            color: Colors.black,
          ),
          onChanged: (String newValue) {
          if (newValue!=measureW){
            if (newValue=='kg'){
              isgoal=false;
              setW((weight*0.45).round()>30?(weight*0.45).round():30,newValue);
              isgoal=true;
              setW((goal*0.45).round()>30?(goal*0.45).round():30,newValue);
              isgoal=false;
            }
            else{
              isgoal=false;
              setW((weight/0.45).round(),newValue);
              isgoal=true;
              setW((goal/0.45).round(),newValue);
              isgoal=false;
            }
          }
          },
          items: <String>['kg', 'lb'].map<DropdownMenuItem<String>>((String value) {
            return DropdownMenuItem<String>(
              value: value,
              child: Text(AppLocalizations.of(context).translate(value))

            );
          }).toList(),
        )
      ]);

  }

}
class _HeightPickerState extends State<HeightPicker> with AfterInitMixin<HeightPicker>{
  int height,heightF,heightI;
  String measure;
  SharedPreferences pref;
  getH() async{
    var a=pref.getString("measureH")??'cm';
    setState(() {
      height = pref.getInt("height") ?? 150;
      heightF=pref.getInt("feet")??5;
      heightI=pref.getInt("inch")??0;
    });
    if (a=='cm') {
      setState(() {
        measure='cm';
      });
    }
    else{

      setState(() {
        measure='f/in';
      });
    }

  }
  setH(int w) async{
    setState(() {
      height=w;
    });
    pref.setInt("height",w);
    pref.setString("measureH", "cm");
  }
  setHF(int w) async{ // todo
    setState(() {
      heightF=w;
    });
    pref.setInt("feet",w);
    pref.setString("measureH", "f/in");
  }
  setHI(int w) async{ // todo
    setState(() {
      heightI=w;
    });
    pref.setInt("inch",w);
  }
  @override void didInitState() {
    pref=pref=Provider.of<Data>(context).prefs;
    getH();
  }
  @override
  Widget build(BuildContext context) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceAround,
      children: <Widget>[
        (measure=='cm')?Stack(children: [Theme(
            data: Theme.of(context).copyWith(
              accentColor: Colors.black,
            ),
            child: NumberPicker.integer(initialValue: height, minValue: 30, maxValue: 270, onChanged: (newValue)=>setH(newValue))),
          Positioned(top: 55,left: 35,child: Container(height: 2,width: 30,color: Color.fromARGB(255,207,78,61),)),
          Positioned(top: 91,left: 35,child: Container(height: 2,width: 30,color: Color.fromARGB(255,207,78,61),))])
        :Row(
          children: <Widget>[
            Stack(children: [Theme(
                data: Theme.of(context).copyWith(
                  accentColor: Colors.black,
                ),
                child:             NumberPicker.integer(initialValue: heightF, minValue: 2, maxValue: 10, onChanged: (newValue)=>setHF(newValue))),

                Positioned(top: 55,left: 35,child: Container(height: 2,width: 30,color: Color.fromARGB(255,207,78,61),)),
              Positioned(top: 91,left: 35,child: Container(height: 2,width: 30,color: Color.fromARGB(255,207,78,61),))]),
            Stack(children: [Theme(
                data: Theme.of(context).copyWith(
                  accentColor: Colors.black,
                ),
                child:            NumberPicker.integer(initialValue: heightI, minValue: 0, maxValue: 11, onChanged: (newValue)=>setHI(newValue))),

              Positioned(top: 55,left: 35,child: Container(height: 2,width: 30,color: Color.fromARGB(255,207,78,61),)),
              Positioned(top: 91,left: 35,child: Container(height: 2,width: 30,color: Color.fromARGB(255,207,78,61),))])]
        ),
        DropdownButton<String>(value: measure,iconSize: 24,elevation: 16,
          underline: Container(
            height: 2,
            color: Colors.black,
          ),
          onChanged: (String newValue) {
            setState(() {
              measure=newValue;

            });
            (measure=='cm')?setH(height):setHF(heightF);
          },
          items: <String>['cm', 'f/in'].map<DropdownMenuItem<String>>((String value) {
            return DropdownMenuItem<String>(
              value: value,
              child: Text(AppLocalizations.of(context).translate(value)),
            );
          }).toList(),
        ),
      ],
    );
  }

}

class RadioLang extends StatefulWidget{
  AppLanguage appLanguage;
  RadioLang({this.appLanguage});
  @override
  createState()=>new _RadioLangState();
}
class _RadioLangState extends State<RadioLang>{
  //AppLanguage appLanguage;
  String lang;
  //_RadioLangState(this.appLanguage);
  @override
  void initState() {
    //appLanguage.fetchLocale();
    //lang=appLanguage._appLocale.toString();
    super.initState();
  }
  @override
  Widget build(BuildContext context) {

    var appLanguage = Provider.of<AppLanguage>(context);
    lang=appLanguage.applocale.languageCode.toString();
    //print(lang);
    return Column(
      children: <Widget>[
        InkWell(
          child: Padding(
            padding: const EdgeInsets.all(12.0),
            child: Row(children: <Widget>[
              Text("Russian"),
              Spacer(),
              lang=='ru'?Icon(Icons.check,color: Colors.redAccent,):Text("")
            ],),
          ),
        onTap: (){
          if (lang!='ru'){appLanguage.changeLanguage(Locale('ru'));
          //print(appLanguage._appLocale.toString());
          Phoenix.rebirth(context);}
        },),
        Container(height: 1,width: MediaQuery.of(context).size.width-50,color: Colors.grey.shade300,),
        InkWell(
          child: Padding(
            padding: const EdgeInsets.all(12.0),
            child: Row(children: <Widget>[
              Text("English"),
              Spacer(),
              lang=='en'?Icon(Icons.check,color: Colors.redAccent,):Text("")
            ],),
          ),
          onTap: (){
            if (lang!="en"){
            appLanguage.changeLanguage(Locale('en'));
            //print(appLanguage._appLocale.toString());
            Phoenix.rebirth(context);}
          },),
      ],
    );
  }
}
class MainSettings extends StatefulWidget{
  @override
  _MainSettingsState createState()=>_MainSettingsState();
}

class _MainSettingsState extends State<MainSettings> with AfterInitMixin<MainSettings>{
  Future<String> get _localPath async {
    final directory = await getApplicationDocumentsDirectory();
    // For your reference print the AppDoc directory
    print(directory.path);
    return directory.path;
  }
  Future<File> get _localFile async {
    final path = await _localPath;
    return File('$path/data.txt');
  }
  Future<File> deleteContent() async {
    final file = await _localFile;
    // Write the file
    //DateTime.now().w
    //return file.writeAsString("2 6 2020 110 5 7\n");
    if (file.exists()!=null)
    return file.delete();
    else
      return null;
  }
//  daily(FlutterLocalNotificationsPlugin flutterLocalNotificationsPlugin,int hour,int minute)async{
//    var time = Time(hour, minute, 0);
//    var androidPlatformChannelSpecifics =
//    AndroidNotificationDetails('repeatDailyAtTime channel id',
//        'repeatDailyAtTime channel name', 'repeatDailyAtTime description');
//    var iOSPlatformChannelSpecifics =
//    IOSNotificationDetails();
//    var platformChannelSpecifics = NotificationDetails(
//        androidPlatformChannelSpecifics, iOSPlatformChannelSpecifics);
//    //await FlutterLocalNotificationsPlatform;
//    await flutterLocalNotificationsPlugin.showDailyAtTime(
//      0,
//      AppLocalizations.of(context).translate("notifhead"),
//      AppLocalizations.of(context).translate("notifbody"),
//      time,
//      platformChannelSpecifics,
//    );
  //}
  myTimePicker(context){
    List<int> children=new List();
    List<int> children1=new List();

    for (int i=0;i<60;i++)
{   if (i!=0 && i<=12)   children.add(i);
children1.add(i);
}    showModalBottomSheet(
        context: context,
        shape: RoundedRectangleBorder(borderRadius: BorderRadius.only(topRight: Radius.circular(18),topLeft: Radius.circular(18))),
        builder: (BuildContext context) {
          //print((((((prefs.getInt("notification")/100).floor())%12)==0)?12:(prefs.getInt("notification")/100).floor()%12));
          return Container(

            height: 355,
            width: MediaQuery.of(context).size.width,
            padding: EdgeInsets.all(20),
            child: Column(mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[
                Text(AppLocalizations.of(context).translate("nexttrain"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 18),),
                Container(
                  height: 190,
                  child: Row(
                    mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                    children: <Widget>[
                      Container(
                        width: 70,
                       //child: Cupert,
                       child: CupertinoPicker(children: children.map((e) => Center(child: Text(e.toString()))).toList(),itemExtent: 40,
                       highlighterBorder: Color.fromARGB(255, 207, 78, 61),highlighterBorderWidth: 1.5,onSelectedItemChanged: (value){
                         hour=value+1;
                         },scrollController: new FixedExtentScrollController(initialItem: (((((prefs.getInt("notification")/100).floor())%12)==0)?12:(prefs.getInt("notification")/100).floor()%12-1)))
                              //backgroundColor: Colors.blue,


                       ),
                      Container(
                          width: 70,
                          //child: Cupert,
                          child: CupertinoPicker(children: children1.map((e) => Center(child: Text(e.toString()))).toList(),itemExtent: 40,
                            highlighterBorder: Color.fromARGB(255, 207, 78, 61),highlighterBorderWidth: 1.5,onSelectedItemChanged: (value){
                            minute=value;
                            },scrollController: new FixedExtentScrollController(initialItem: prefs.getInt("notification")%100),)
                        //backgroundColor: Colors.blue,


                      ),
                      Container(
                          width: 70,
                          //child: Cupert,
                          child: CupertinoPicker(children: [Center(child: Text("am")),Center(child: Text("pm"))],itemExtent: 40,
                            highlighterBorder: Color.fromARGB(255, 207, 78, 61),highlighterBorderWidth: 1.5,onSelectedItemChanged: (value){
                              pm=(value==1);
                            },scrollController: new FixedExtentScrollController(initialItem: ((((prefs.getInt("notification")/100).floor())>12)?1:0)),)
                        //backgroundColor: Colors.blue,


                      ),
                    ],
                  ),
                ),
          Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly,crossAxisAlignment: CrossAxisAlignment.end,children: <Widget>[
          SizedBox(
          width: MediaQuery.of(context).size.width/2-50,
          height: 40,
          child: new OutlineButton(child: new Text(AppLocalizations.of(context).translate("cancel")),color: Colors.white,onPressed: (){
          Navigator.of(context).pop();},textColor: Colors.black,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0),)),
          ),
          SizedBox(
            height: 40,
          width: MediaQuery.of(context).size.width/2-50,
          child: new FlatButton(child: new Text(AppLocalizations.of(context).translate("sbmt")),color: Color.fromARGB(255,207,78,61),
          onPressed: ()async{
            int b=hour*100+(pm?1:0)*1200+minute;
            //print(hour.toString()+pm.toString());
              Provider.of<Data>(context,listen: false).prefs.setInt("notification", b);
              //fetchnotif();
            setState(() {

            });
            DateTime d=DateTime.now(),dd;
            dd=new DateTime(d.year,d.month,d.day,(b/100).floor(),b%100);
            if ((b/100).floor()<d.hour || ((b/100).floor()==d.hour && b%100<=d.minute))
            {
              //print('add');
              dd=dd.add(Duration(days:1));

            }
            await AndroidAlarmManager.cancel(alarmId);
            await AndroidAlarmManager.oneShotAt(dd, alarmId, not);
              //print(Provider.of<Data>(context,listen: false).plugin);
              //daily(Provider.of<Data>(context,listen: false).plugin, hour+(pm?1:0)*12, minute);
          Navigator.of(context).pop();},textColor: Colors.white,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0))),
          ),
              ],
            )]));
          }
    );

  }
//  myDatePicker(context){
//    List<int> children=new List();
//    List<int> children1=new List();
//    List<int> children2=new List();
//    for (int i=0;i<60;i++)
//    {   if (i!=0 && i<=12)   children.add(i);
//    children1.add(i);
//    }    showModalBottomSheet(
//        context: context,
//        shape: RoundedRectangleBorder(borderRadius: BorderRadius.only(topRight: Radius.circular(18),topLeft: Radius.circular(18))),
//        builder: (BuildContext context) {
//          //print((((((prefs.getInt("notification")/100).floor())%12)==0)?12:(prefs.getInt("notification")/100).floor()%12));
//          return Container(
//
//              height: 355,
//              width: MediaQuery.of(context).size.width,
//              padding: EdgeInsets.all(20),
//              child: Column(mainAxisAlignment: MainAxisAlignment.spaceBetween,
//                  children: <Widget>[
//                    Text(AppLocalizations.of(context).translate("nexttrain"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 18),),
//                    Container(
//                      height: 190,
//                      child: Row(
//                        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
//                        children: <Widget>[
//                          Container(
//                              width: 70,
//                              //child: Cupert,
//                              child: CupertinoPicker(children: children.map((e) => Center(child: Text(e.toString()))).toList(),itemExtent: 40,
//                                  highlighterBorder: Color.fromARGB(255, 207, 78, 61),highlighterBorderWidth: 1.5,onSelectedItemChanged: (value){
//                                    hour=value+1;
//                                  },scrollController: new FixedExtentScrollController(initialItem: (((((prefs.getInt("notification")/100).floor())%12)==0)?12:(prefs.getInt("notification")/100).floor()%12-1)))
//                            //backgroundColor: Colors.blue,
//
//
//                          ),
//                          Container(
//                              width: 70,
//                              //child: Cupert,
//                              child: CupertinoPicker(children: children1.map((e) => Center(child: Text(e.toString()))).toList(),itemExtent: 40,
//                                highlighterBorder: Color.fromARGB(255, 207, 78, 61),highlighterBorderWidth: 1.5,onSelectedItemChanged: (value){
//                                  minute=value;
//                                },scrollController: new FixedExtentScrollController(initialItem: prefs.getInt("notification")%100),)
//                            //backgroundColor: Colors.blue,
//
//
//                          ),
//                          Container(
//                              width: 70,
//                              //child: Cupert,
//                              child: CupertinoPicker(children: [Center(child: Text("am")),Center(child: Text("pm"))],itemExtent: 40,
//                                highlighterBorder: Color.fromARGB(255, 207, 78, 61),highlighterBorderWidth: 1.5,onSelectedItemChanged: (value){
//                                  pm=(value==1);
//                                },scrollController: new FixedExtentScrollController(initialItem: ((((prefs.getInt("notification")/100).floor())>12)?1:0)),)
//                            //backgroundColor: Colors.blue,
//
//
//                          ),
//                        ],
//                      ),
//                    ),
//                    Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly,crossAxisAlignment: CrossAxisAlignment.end,children: <Widget>[
//                      SizedBox(
//                        width: MediaQuery.of(context).size.width/2-50,
//                        height: 40,
//                        child: new OutlineButton(child: new Text(AppLocalizations.of(context).translate("cancel")),color: Colors.white,onPressed: (){
//                          Navigator.of(context).pop();},textColor: Colors.black,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0),)),
//                      ),
//                      SizedBox(
//                        height: 40,
//                        width: MediaQuery.of(context).size.width/2-50,
//                        child: new FlatButton(child: new Text(AppLocalizations.of(context).translate("sbmt")),color: Color.fromARGB(255,207,78,61),
//                            onPressed: (){
//                              int b=hour*100+(pm?1:0)*1200+minute;
//                              //print(hour.toString()+pm.toString());
//                              Provider.of<Data>(context,listen: false).prefs.setInt("notification", b);
//                              //fetchnotif();
//                              setState(() {
//
//                              });
//                              //print(Provider.of<Data>(context,listen: false).plugin);
//                              daily(Provider.of<Data>(context,listen: false).plugin, hour+(pm?1:0)*12, minute);
//                              Navigator.of(context).pop();},textColor: Colors.white,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0))),
//                      ),
//                    ],
//                    )]));
//        }
//    );
//
//  }
  SharedPreferences prefs;
  int notif;
  //int notifh;
  //int notifm;
  bool pm;
  int hour,minute;
  @override
  didInitState(){
    prefs=Provider.of<Data>(context).prefs;
//    hour=DateTime.now().hour%12==0?12:DateTime.now().hour%12;
//    minute=DateTime.now().minute;
//    pm=(DateTime.now().hour>12);
    hour=(prefs.getInt("notification")/100).floor()%12==0?12:(prefs.getInt("notification")/100).floor()%12;
    minute=(prefs.getInt("notification")%100);
    pm=(prefs.getInt("notification")/100).floor()>12;
    //fetchnotif();
  }
//  fetchnotif(){
//    setState(() { notif=prefs.getInt("notification")??1830;
//    hour=(notif/100).floor();
//    hour>12?pm=true:pm=false;
//    hour>12?hour-=12:hour=hour;
//    minute=notif%100;});
//  }
  @override
  Widget build(BuildContext context) {


    return Scaffold(
      backgroundColor: Color.fromARGB(255, 230, 230, 230),
      appBar: AppBar(title: Text(AppLocalizations.of(context).translate("settings"),style: TextStyle(color: Colors.black),),iconTheme: IconThemeData(color: Colors.black),),
      body:  Column(
        children: <Widget>[

          SizedBox(width: MediaQuery.of(context).size.width,child: FlatButton(color:Colors.white,child:  Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: <Widget>[
              Text(AppLocalizations.of(context).translate("notif")),
    Text(((hour/10).floor()==0?"0":"")+hour.toString()+':'+((minute/10).floor()==0?"0":"")+minute.toString()+' '+(pm?"pm":"am")),]
          ),onPressed:()async {
            //DateTime a= await DatePicker.showTimePicker(context,showSecondsColumn: false);
             myTimePicker(context);
            //fetchnotif();
//            if (a!=null){
//              int b=a.hour*100+a.minute;
//              Provider.of<Data>(context,listen: false).prefs.setInt("notification", b);
//              //print(Provider.of<Data>(context,listen: false).plugin);
            //print(hour.toString()+minute.toString()+pm.toString());
              //daily(Provider.of<Data>(context,listen: false).plugin, hour+(pm?12:0), minute);
//            }
//            fetchnotif();
            },)),
          SizedBox(width: MediaQuery.of(context).size.width,child: FlatButton(color:Colors.white,child: Align(alignment:Alignment.centerLeft,child: Text(AppLocalizations.of(context).translate("privacy"))),onPressed: (){Navigator.push(context, new MaterialPageRoute(builder: (context)=>new Privacy()));},)),

          SizedBox(width: MediaQuery.of(context).size.width,child: FlatButton(color:Colors.white,child: Align(alignment:Alignment.centerLeft,child: Text(AppLocalizations.of(context).translate("delete"),style: TextStyle(color: Colors.red))),onPressed: (){Provider.of<Data>(context,listen: false).prefs.clear(); deleteContent(); Phoenix.rebirth(context);},)),

        ],
      ),
    );
  }
}
class Privacy extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text(AppLocalizations.of(context).translate("privacy"),style: TextStyle(color: Colors.black),),backgroundColor: Color.fromARGB(255, 230, 230, 230),iconTheme: IconThemeData(color: Colors.black),),
      body: WebView(
        initialUrl: "https://devsteam.mobi/privacyPolicy.html",
      ),
    );
  }
}

class AboutMe extends StatelessWidget{
  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Container(
        child: Scaffold(
          backgroundColor: Color.fromARGB(100, 200, 200, 200),
          appBar: AppBar(
            title: new Text(AppLocalizations.of(context).translate("tab3"),style: TextStyle(color: Colors.black),),
          ),
          body: Center(
            child: Column(
              children: <Widget>[
                Container(
                  decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.all(Radius.circular(10))),
                  width: 370,
                  child: Column(

                    children: <Widget>[
                      Padding(
                        padding: const EdgeInsets.all(8.0),
                        child: Align(alignment:Alignment.topLeft,child: Text(AppLocalizations.of(context).translate("settings"),style: TextStyle(fontSize: 20,fontWeight: FontWeight.bold),)),
                      ),
                      SettingsButton(AppLocalizations.of(context).translate("myprofile"),(){Navigator.push(context, MaterialPageRoute(builder: (context)=>MyProfile()));},Icon(Icons.account_box)),
                      SettingsButton(AppLocalizations.of(context).translate("settings"),(){Navigator.push(context, MaterialPageRoute(builder: (context)=>MainSettings()));},Icon(Icons.settings)),
                      SettingsButton(AppLocalizations.of(context).translate("lng"),(){Navigator.push(context, MaterialPageRoute(builder: (context)=>LanguageChange(/*appLanguage: Provider.of<AppLanguage>(context),*/)),);},Icon(Icons.language)), // todo не находит нужный эппленг
                    ],
                  ),
                ),
          Container(
            margin: EdgeInsets.only(top: 10,bottom: 10),
            decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.all(Radius.circular(10))),
            width: 370,child: SettingsButton(AppLocalizations.of(context).translate("rate"), (){rateMe(context);}, Icon(Icons.star),)),
                Text(AppLocalizations.of(context).translate("vrs")+":"+Provider.of<Data>(context).version)
              ],
            ),
          ),
        ),
      ),
    );
  }

}
