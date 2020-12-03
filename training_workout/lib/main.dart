import 'dart:async' as async;
import 'dart:io' as Platform;

import 'package:after_init/after_init.dart';
import 'package:bot_toast/bot_toast.dart';
import 'package:firebase_admob/firebase_admob.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_localizations/flutter_localizations.dart';
import 'package:flutter_phoenix/flutter_phoenix.dart';
import 'package:local_notifications/local_notifications.dart';
import 'package:numberpicker/numberpicker.dart';
import 'package:percent_indicator/circular_percent_indicator.dart';
import 'package:provider/provider.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:url_launcher/url_launcher.dart';
import 'localization.dart';
import 'aboutme.dart';
import 'workout.dart';
import 'day.dart' as day;
import 'data.dart';
import 'package:http/http.dart' as http;
import 'dart:isolate';

import 'dart:ui' as ui;
import 'package:android_alarm_manager/android_alarm_manager.dart';



const AndroidNotificationChannel channel = const AndroidNotificationChannel(
    id: 'default_notification',
    name: 'Default',
    description: 'Grant this app the ability to show notifications',

    importance: AndroidNotificationChannelImportance.HIGH
);
final int alarmId=0;
void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  if (Platform.Platform.isAndroid)
  await FirebaseAdMob.instance.initialize(appId: "ca-app-pub-8323348147242911~1836148744");
  else if (Platform.Platform.isIOS)
    await FirebaseAdMob.instance.initialize(appId: "ca-app-pub-8323348147242911~5200678680");

  await AndroidAlarmManager.initialize();
      runApp(
    Phoenix(child: MyApp()),
  );
  SharedPreferences prefs=await SharedPreferences.getInstance();
  await LocalNotifications.createAndroidNotificationChannel(channel: channel,);

  //await LocalNotifications.createNotification(title: "po", content: "po", id: 1);
  //await not1();


  //final int alarmId=0;
  //startForegroundService();

}

class Preloader extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(debugShowCheckedModeBanner:false,

        home:
    Scaffold(

      body: Center(child: Container(width: MediaQuery.of(context).size.width-50,child: Text(AppLocalizations.of(context).translate("ourappname"),textAlign: TextAlign.center,style: TextStyle(color: Colors.white,fontSize: 28,fontWeight: FontWeight.bold),))),
      backgroundColor: Colors.redAccent,));
  }
}
class Weight extends StatefulWidget {
  @override
  _WeightState createState() => _WeightState();
}

class MyPicker1 extends StatelessWidget {
  final int init;
  final onchange;
  MyPicker1( this.init,this.onchange);
  @override
  Widget build(BuildContext context) {
    return NumberPicker.integer(highlightSelectedValue:true,initialValue: init, minValue: 66, maxValue: 333, onChanged: onchange,itemExtent: 60,);//(newValue)=>setW(newValue,measureW))),
  }
}
class Height extends StatefulWidget {
  @override
  _HeightState createState() => _HeightState();
}

class _HeightState extends State<Height> {
  String measure="cm";
  int height=150,heightF=5,heightI=0;
  @override
  Widget build(BuildContext context) {
    return Expanded(
      flex: 1,
      child: Theme(
         data: Theme.of(context).copyWith(
          accentColor: Color.fromARGB(255, 207, 78, 61),
          textTheme: Theme.of(context).textTheme.copyWith(bodyText2: TextStyle(color: Colors.grey.shade500,fontSize: 30,height: 0.5,fontWeight: FontWeight.bold),headline5: TextStyle(fontSize: 50,height: 0.5,fontWeight: FontWeight.bold)
          )),
        child: Stack(
          //mainAxisAlignment: MainAxisAlignment.spaceAround,
          children: <Widget>[
            Positioned(
              top: 65,
              left: ( measure=='cm')?95:150*-1+ MediaQuery.of(context).size.width/2 ,
              child: Container(
                //transform: Matrix4.translationValues(-85, 0, 0),
                //padding: EdgeInsets.only(right:10),
                height: 200,
                width: (measure=='cm')?240:300,
                child: CupertinoPicker(
                  //diameterRatio: 2.5,

                    itemExtent: 50 ,
                    onSelectedItemChanged: (index){ setState(() {
                      String newValue=index==0?"cm":"f/in";
                      if (newValue!=measure){
                        Provider.of<Data>(context,listen: false).prefs.setString("measureH", newValue);
                        setState(() {
                          measure=newValue;
                        });

                      }
                    });},
                    children: [Align(alignment: Alignment.centerRight,child: Text(AppLocalizations.of(context).translate("cm"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 30,color: measure=='cm'?Color.fromARGB(255, 207, 78, 61):Colors.grey),)),Align(alignment: Alignment.centerRight,child: Text(AppLocalizations.of(context).translate("f/in"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 30,color: measure=='f/in'?Color.fromARGB(255, 207, 78, 61):Colors.grey)))]
                ),
              ),
            ),
            (measure=='cm')?
               Positioned(top:100,left: MediaQuery.of(context).size.width/2-120,
                   child: NumberPicker.integer(initialValue: height, minValue: 30, maxValue: 270, onChanged: (newValue){
                     Provider.of<Data>(context,listen: false).prefs.setInt("height", newValue);
                   setState((){height=newValue;});}))

                :Positioned(
                  top: 100,
                  left: MediaQuery.of(context).size.width/2-180,
                  child: Row(
                  children: <Widget>[
                    NumberPicker.integer(initialValue: heightF, minValue: 2, maxValue: 10, onChanged: (newValue){Provider.of<Data>(context,listen: false).prefs.setInt("feet", newValue);
                    setState((){heightF=newValue;});}),
                   NumberPicker.integer(initialValue: heightI, minValue: 0, maxValue: 11, onChanged: (newValue){Provider.of<Data>(context,listen: false).prefs.setInt("inch", newValue);
                   setState((){heightI=newValue;});}),

                    ]
            ),
                ),

            Positioned(top:0,width: MediaQuery.of(context).size.width,child: Text(AppLocalizations.of(context).translate("urh8"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 30),textAlign: TextAlign.center,)),
          ],
        ),
      ),
    );;
  }
}

class _WeightState extends State<Weight> {
    String measureW='kg';
    int weight=50;
   @override
    Widget build(BuildContext context) {
      //pref.setInt("weight", 100);
      //pref.setInt("toweight", 100);
      //init=isgoal?(goal==-1?weight:goal):weight;
      return Expanded(
        flex: 1,
        child: Theme(
            data: Theme.of(context).copyWith(
              accentColor: Color.fromARGB(255, 207, 78, 61),
              textTheme: Theme.of(context).textTheme.copyWith(bodyText2: TextStyle(color: Colors.grey.shade500,fontSize: 30,height: 0.5,fontWeight: FontWeight.bold),headline5: TextStyle(fontSize: 50,height: 0.5,fontWeight: FontWeight.bold)
              ),
            ),
            child:Stack(
            //  crossAxisAlignment: CrossAxisAlignment.end,
          //crossAxisAlignment: CrossAxisAlignment.center,
           // mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[


            Positioned(
              //top: 200,
              left: MediaQuery.of(context).size.width/2-105,
              top: 80,
              child: Container(
              //transform: Matrix4.translationValues(-85, 0, 0),
          padding: EdgeInsets.only(right:10),
          height: 200,
          width: 210,
          child: CupertinoPicker(
            //diameterRatio: 2.5,

                itemExtent: 50 ,
                onSelectedItemChanged: (index){ setState(() {
                  //print(Provider.of<Data>(context,listen: false).prefs.getKeys());
                  String newValue=index==0?"kg":"lb";
                  if (newValue!=measureW){
                    Provider.of<Data>(context,listen: false).prefs.setString("measureW", newValue);
                    if (newValue=='kg'){

                      setState(() {
                        weight=(weight*0.45).round()>30?(weight*0.45).round():30;
                        measureW=newValue;
                      });

                    }
                    else{
                      setState(() {
                        weight=(weight/0.45).round()<333?(weight/0.45).round():332;
                        measureW=newValue;
                      });
                    }
                  }
                });},
                children: [Align(alignment: Alignment.centerRight,child: Text(AppLocalizations.of(context).translate("kg"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 30,color: measureW=='kg'?Color.fromARGB(255, 207, 78, 61):Colors.grey),)),Align(alignment: Alignment.centerRight,child: Text(AppLocalizations.of(context).translate("lb"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 30,color: measureW=='lb'?Color.fromARGB(255, 207, 78, 61):Colors.grey)))]
          ),
        ),
            ),
              Positioned(top: 100,left: MediaQuery.of(context).size.width/2-120,child: measureW=='kg'?new NumberPicker.integer(itemExtent:60,highlightSelectedValue:true,initialValue: weight, minValue: 30, maxValue: 150, onChanged: (newValue){Provider.of<Data>(context,listen: false).prefs.setInt("weight", newValue);
              setState(() {
                        weight=newValue;
                  });})
                      :new MyPicker1(weight,(newValue){Provider.of<Data>(context,listen: false).prefs.setInt("weight", newValue);
                      setState(() {
                        weight=newValue;
                      });}),

              ),
              Positioned(top:0,width: MediaQuery.of(context).size.width,child: Text(AppLocalizations.of(context).translate("urw8"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 30),textAlign: TextAlign.center,)),

//
            ])),
      );



  }
}

class Questionere extends StatefulWidget {
  @override
  _QuestionereState createState() => _QuestionereState();
}
class Loading extends StatefulWidget {
  int index;
  Loading({this.index});
  @override
  _LoadingState createState() => _LoadingState(index: index);
}
class YourPlan extends StatelessWidget {
  int index;
  YourPlan({this.index});
  @override
  Widget build(BuildContext context) {
    return SafeArea(

        child: Scaffold(
          body:  Container(
            height: MediaQuery.of(context).size.height,child: Stack(
              children: <Widget>[
                Column(children: <Widget>[
                Container(margin: EdgeInsets.only(top: 50,bottom: 20),child: Text(AppLocalizations.of(context).translate("planrdy"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 26),)),
                Center(child: Container(margin: EdgeInsets.only(bottom: 50),width: MediaQuery.of(context).size.width*0.65,child: Text(AppLocalizations.of(context).translate("wepickplan"),style: TextStyle(fontSize: 16),textAlign: TextAlign.center,),)),
                Container(child: Image.asset("assets/your"+(3-index).toString()+".jpg",width: MediaQuery.of(context).size.width*0.90,)),

          ],),
                Positioned(bottom: 20,left:25,child: SizedBox(width: MediaQuery.of(context).size.width-50,height:50,child: FlatButton(shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(15 ))),color: Color.fromARGB(255, 207, 78, 61),child: Text(AppLocalizations.of(context).translate("continue").toUpperCase(),style: TextStyle(color: Colors.white, fontSize: 20),),onPressed: (){ Navigator.pushReplacement(context, new MaterialPageRoute(builder: (context)=>MainTabs(index: 3-index)));},)))
              ],
            ),
        ),
      ),
    );
  }
}

class _LoadingState extends State<Loading> {
  double perc=0;
  int i=1;
  int index;

  async.Timer t;
  List<double> m=[25/15000,35/15000,15/15000,25/15000];
  DateTime date;
  _LoadingState({this.index});
  @override
  void initState() {
    date= DateTime.now();
    t=new async.Timer.periodic(Duration(milliseconds: 10), (timer) {
      if (DateTime.now().difference(date).inMilliseconds<=1500)
        if (perc<=1)
      setState(() {
        perc+=m[i-1];

      });
        else
          {t.cancel();
          Navigator.pushReplacement(
               context, new MaterialPageRoute(builder: (context) => YourPlan(index: index)));
          }
      //print(DateTime.now().difference(date));
      if (DateTime.now().difference(date).inSeconds>=2) {
          date=date.add(Duration(seconds: 2));
        if (i == 4) {
          //t.cancel();
         //
        }
        else
          setState(() {
            i = i + 1;
          });
      }
    });
    super.initState();
  }
  @override
  Widget build(BuildContext context) {

    return SafeArea(
      child: Scaffold(
        body: Container(
          width: MediaQuery.of(context).size.width,
          child: Column(crossAxisAlignment: CrossAxisAlignment.center,children: <Widget>[
            Container(margin: EdgeInsets.only(top: 100,bottom: 30),child: Text(AppLocalizations.of(context).translate("creatingplan"),style: TextStyle(fontSize: 26,fontWeight: FontWeight.bold),),),
            Container(margin: EdgeInsets.only(bottom: 100),child: Text(AppLocalizations.of(context).translate("plan"+((i>4)?4:i).toString()))),
            CircularPercentIndicator(
              lineWidth: 15,
              backgroundColor: Colors.grey.shade200,
              radius: 150,
              percent: perc>1?1:perc,
              progressColor: Color.fromARGB(255, 207, 78, 67),
              center: Text((perc*100).round().toString()+"%",style: TextStyle(fontSize: 40,fontWeight: FontWeight.bold)),
            )
          ],),
        ),
      ),
    );
  }
}

class _QuestionereState extends State<Questionere> with TickerProviderStateMixin{
  int index=0,goalindex=-1,squats=-1;
  @override
  Widget build(BuildContext context) {
    TabController t=new TabController(length: 4, vsync: this);
    t.addListener(() {if(t.indexIsChanging) setState(() {
index=t.index;
    });});
    return
       Scaffold(
        appBar: AppBar(actions:[Center(child: FlatButton(onPressed:(){Navigator.pushReplacement(context, new MaterialPageRoute(builder: (context)=>MainTabs()));}
        ,child: Text(AppLocalizations.of(context).translate("skip"),style: TextStyle(color: Colors.grey),)))],leading: index!=0?FlatButton(child: Icon(Icons.arrow_back),onPressed: (){t.animateTo(index-1);},):Text(""),iconTheme: (IconThemeData(color: Colors.black)),
          title: Padding(
            padding: const EdgeInsets.only(left:58.0),
            child: Row(mainAxisAlignment: MainAxisAlignment.center,children: <Widget>[Container(margin:EdgeInsets.all(3),width: 20,height: 2,color: index==0?Colors.redAccent:Colors.grey.shade300 ,),
              Container(margin:EdgeInsets.all(3),width: 20,height: 2,color: index==1?Colors.redAccent:Colors.grey.shade300,),
              Container(margin:EdgeInsets.all(3),width: 20,height: 2,color: index==2?Colors.redAccent:Colors.grey.shade300,),
              Container(margin:EdgeInsets.all(3),width: 20,height: 2,color: index==3?Colors.redAccent:Colors.grey.shade300,),
            ],),
          ),),
        body: TabBarView(
          controller: t,
          physics: NeverScrollableScrollPhysics(),
          children: <Widget>[Container(child: Column(mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: <Widget>[
              Column( children: <Widget>[
                Padding(
                  padding: const EdgeInsets.only(top:18.0,bottom: 60),
                  child: Text(AppLocalizations.of(context).translate("firstgoal",),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 26),),
                ),
                Container(
                  margin: EdgeInsets.all(15),
                  decoration: BoxDecoration(borderRadius: BorderRadius.all(Radius.circular(15)),border: Border.all(color: goalindex!=0?Colors.grey.shade300:Colors.transparent)),
                  child: Material(color: goalindex==0?Color.fromARGB(255, 207, 78, 61):Colors.white,borderRadius: (BorderRadius.all(Radius.circular(15))),//border: Border.all(color: Colors.black),
                  child: InkWell(onTap:(){setState(() {
                    goalindex=0;
                  });},child: Padding(
                    padding: const EdgeInsets.all(20.0),
                    child: Row(mainAxisAlignment: MainAxisAlignment.start,
                      children: <Widget>[
                        Container(height:50,width: 50,margin: EdgeInsets.only(right: 20),decoration: BoxDecoration(shape: BoxShape.circle,image: new DecorationImage(image: new AssetImage("assets/ass.jpg"),fit: BoxFit.fill))),
                        Expanded(flex:1,child: Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[Text(AppLocalizations.of(context).translate("ass"),style: TextStyle(color: goalindex==0?Colors.white:Colors.black,fontSize: 20, fontWeight: FontWeight.bold),),Icon(Icons.check_circle,color: goalindex==0?Colors.white:Colors.transparent,size: 36,)],)),
                      ],
                    ),
                  ),borderRadius:  BorderRadius.all(Radius.circular(10)),)),
                ),
                Container(
                  margin: EdgeInsets.all(15),
                  decoration: BoxDecoration(borderRadius: BorderRadius.all(Radius.circular(15)),border: Border.all(color: goalindex!=1?Colors.grey.shade300:Colors.transparent)),
                  child: Material(color: goalindex==1?Color.fromARGB(255, 207, 78, 61):Colors.white,borderRadius: (BorderRadius.all(Radius.circular(15))),//border: Border.all(color: Colors.black),
                      child: InkWell(onTap:(){setState(() {
                        goalindex=1;
                      });},child: Padding(
                        padding: const EdgeInsets.all(20.0),
                        child: Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,
                          children: <Widget>[
                            Container(height:50,width: 50,margin: EdgeInsets.only(right: 20),decoration: BoxDecoration(shape: BoxShape.circle,image: new DecorationImage(image: new AssetImage("assets/legs.png"),fit: BoxFit.fill))),
                            Expanded(flex:1,child: Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[Text(AppLocalizations.of(context).translate("legs"),style: TextStyle(color: goalindex==1?Colors.white:Colors.black,fontSize: 20, fontWeight: FontWeight.bold),),Icon(Icons.check_circle,color: goalindex==1?Colors.white:Colors.transparent,size: 36,)],)),
                          ],
                        ),
                      ),borderRadius:  BorderRadius.all(Radius.circular(10)),)),
                ),

                ],),
              Container(alignment:Alignment.bottomCenter,height: 50,margin: EdgeInsets.all(15),child: SizedBox(width: MediaQuery.of(context).size.width-50,height:50,child: FlatButton(shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(35 ))),color: goalindex==-1?Colors.grey.shade300:Color.fromARGB(255, 207, 78, 61),child: Text(AppLocalizations.of(context).translate("next").toUpperCase(),style: TextStyle(color: Colors.white, fontSize: 20),),onPressed: (){goalindex!=-1?t.animateTo(1):{};},)))],
          ),),

            Container(child: Column(mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[
                Column( children: <Widget>[
                  Padding(
                    padding: const EdgeInsets.only(top:18.0,bottom: 60),
                    child: RichText(textAlign: TextAlign.center,text: TextSpan(
                      children: [
                        TextSpan(text:AppLocalizations.of(context).translate("feelsquats1",)+' ',style: TextStyle(fontWeight: FontWeight.bold,fontSize: 26,color: Colors.black),),
                        TextSpan(text:"30 ",style: TextStyle(color: Color.fromARGB(255, 207, 78, 61),fontSize: 30,fontWeight: FontWeight.bold),),
                        TextSpan(text:AppLocalizations.of(context).translate("feelsquats2",),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 26,color: Colors.black),),
                      ],)
                    ),
                  ),
                  Container(
                    margin: EdgeInsets.only(left:15,top: 5,bottom: 8),
                    decoration: BoxDecoration(borderRadius: BorderRadius.all(Radius.circular(15)),border: Border.all(color: squats!=0?Colors.grey.shade300:Colors.transparent)),
                    child: Material(color: squats==0?Color.fromARGB(255, 207, 78, 61):Colors.white,borderRadius: (BorderRadius.all(Radius.circular(15))),//border: Border.all(color: Colors.black),
                        child: InkWell(onTap:(){setState(() {
                          squats=0;
                        });},child: Padding(
                          padding: const EdgeInsets.all(15.0),
                          child: Row(mainAxisAlignment: MainAxisAlignment.start,
                            children: <Widget>[
                              Container(height:50,width: 50,margin: EdgeInsets.only(right: 20),decoration: BoxDecoration(shape: BoxShape.circle,image: new DecorationImage(image: new AssetImage("assets/happy.jpg"),fit: BoxFit.fill))),
                              Expanded(flex:1,child: Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[Text(AppLocalizations.of(context).translate("veasy"),style: TextStyle(color: squats==0?Colors.white:Colors.black,fontSize: 20, fontWeight: FontWeight.bold),),Icon(Icons.check_circle,color: squats==0?Colors.white:Colors.transparent,size: 36,)],)),
                            ],
                          ),
                        ),borderRadius:  BorderRadius.all(Radius.circular(10)),)),
                  ),
                  Container(
                    margin: EdgeInsets.only(left:15,top: 5,bottom: 5),
                    decoration: BoxDecoration(borderRadius: BorderRadius.all(Radius.circular(15)),border: Border.all(color: squats!=1?Colors.grey.shade300:Colors.transparent)),
                    child: Material(color: squats==1?Color.fromARGB(255, 207, 78, 61):Colors.white,borderRadius: (BorderRadius.all(Radius.circular(15))),//border: Border.all(color: Colors.black),
                        child: InkWell(onTap:(){setState(() {
                          squats=1;
                        });},child: Padding(
                          padding: const EdgeInsets.all(15.0),
                          child: Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,
                            children: <Widget>[
                              Container(height:50,width: 50,margin: EdgeInsets.only(right: 20),decoration: BoxDecoration(shape: BoxShape.circle,image: new DecorationImage(image: new AssetImage("assets/soso.jpg"),fit: BoxFit.fill))),
                              Expanded(flex:1,child: Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[Text(AppLocalizations.of(context).translate("tired"),style: TextStyle(color: squats==1?Colors.white:Colors.black,fontSize: 20, fontWeight: FontWeight.bold),),Icon(Icons.check_circle,color: squats==1?Colors.white:Colors.transparent,size: 36,)],)),
                            ],
                          ),
                        ),borderRadius:  BorderRadius.all(Radius.circular(10)),)),
                  ),
                  Container(
                    margin: EdgeInsets.only(left: 15,top: 8),
                    decoration: BoxDecoration(borderRadius: BorderRadius.all(Radius.circular(15)),border: Border.all(color: squats!=2?Colors.grey.shade300:Colors.transparent)),
                    child: Material(color: squats==2?Color.fromARGB(255, 207, 78, 61):Colors.white,borderRadius: (BorderRadius.all(Radius.circular(15))),//border: Border.all(color: Colors.black),
                        child: InkWell(onTap:(){setState(() {
                          squats=2;
                        });},child: Padding(
                          padding: const EdgeInsets.all(15.0),
                          child: Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,
                            children: <Widget>[
                              Container(height:50,width: 50,margin: EdgeInsets.only(right: 20),decoration: BoxDecoration(shape: BoxShape.circle,image: new DecorationImage(image: new AssetImage("assets/bad.jpg"),fit: BoxFit.fill))),
                              Expanded(flex:1,child: Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[Text(AppLocalizations.of(context).translate("thard"),style: TextStyle(color: squats==2?Colors.white:Colors.black,fontSize: 20, fontWeight: FontWeight.bold),),Icon(Icons.check_circle,color: squats==2?Colors.white:Colors.transparent,size: 36,)],)),
                            ],
                          ),
                        ),borderRadius:  BorderRadius.all(Radius.circular(10)),)),
                  ),
                ],),
                Container(alignment:Alignment.bottomCenter,height: 50,margin: EdgeInsets.all(15),child: SizedBox(width: MediaQuery.of(context).size.width-50,height:50,child: FlatButton(shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(35 ))),color: squats==-1?Colors.grey.shade300:Color.fromARGB(255, 207, 78, 61),child: Text(AppLocalizations.of(context).translate("next").toUpperCase(),style: TextStyle(color: Colors.white, fontSize: 20),),onPressed: (){squats!=-1?t.animateTo(2):{};},)))],
            ),),
            Container(child:  Column(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[
              Weight(),
              Align(alignment: Alignment.bottomCenter,child: Container(margin: EdgeInsets.only(bottom: 15),child: SizedBox(width: MediaQuery.of(context).size.width-50,height:50,child: FlatButton(shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(15 ))),color: Color.fromARGB(255, 207, 78, 61),child: Text(AppLocalizations.of(context).translate("next").toUpperCase(),style: TextStyle(color: Colors.white, fontSize: 20),),onPressed: (){t.animateTo(3);},))))
            ],),),
            Container(child:  Column(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[
              Height(),
              Align(alignment: Alignment.bottomCenter,child: Container(margin: EdgeInsets.only(bottom: 15),child: SizedBox(width: MediaQuery.of(context).size.width-50,height:50,child: FlatButton(shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(15 ))),color: Color.fromARGB(255, 207, 78, 61),child: Text(AppLocalizations.of(context).translate("continue").toUpperCase(),style: TextStyle(color: Colors.white, fontSize: 20),),onPressed: (){ Navigator.pushReplacement(context, new MaterialPageRoute(builder: (context)=>Loading(index: squats,)));},))))
            ],)),],
        ),

    );
  }
}

class MyApp extends StatelessWidget {
  Data d;
  bool firststart;



  @override
  Widget build(BuildContext context) {

    d=new Data();
//    d.setPlugin(flutterLocalNotificationsPlugin);
    precacheImage(new AssetImage("assets/train1.jpg"),context);
    precacheImage(new AssetImage("assets/train2.jpg"),context);
    precacheImage(new AssetImage("assets/train3.jpg"),context);
    precacheImage(new AssetImage("assets/end.jpg"),context);
    ////

    /////todo
//    print(ui.window.locale.languageCode);

    return FutureBuilder(
      future: d.update(),
      builder:(BuildContext context, AsyncSnapshot snapshot){


        Widget pr=Preloader();
        if (snapshot.hasData){

          print(snapshot.data.getKeys());
          firststart=snapshot.data.getBool("first");
          snapshot.data.setBool("first",false);
          pr=firststart?Questionere():MainTabs();
        }
        return  Provider<Data>(
        create: (_)=>d,
        child: ChangeNotifierProvider<AppLanguage>(
          create: (_)=>d.appLanguage,
          child: Consumer<AppLanguage>(builder: (context,model,child){return MaterialApp(
            builder: BotToastInit(),
            navigatorObservers: [BotToastNavigatorObserver()],
            supportedLocales: [
              Locale('en', ''),
              Locale('ru', ''),
            ],
            localizationsDelegates: [
              AppLocalizations.delegate,
              GlobalMaterialLocalizations.delegate,
              GlobalWidgetsLocalizations.delegate,
            ],
            locale: d.appLanguage.applocale,
            theme: ThemeData(appBarTheme: AppBarTheme(color: Colors.transparent,elevation: 0),fontFamily: "Lato"),
            debugShowCheckedModeBanner: false,
            home: pr,

          );}
        )),
      );}
    );
  }
}
class MainTabs extends StatefulWidget {
  int index=1;
  MainTabs({this.index});

  @override
  _MainTabsState createState() => _MainTabsState(planindex: index!=null?index-1:-1);
}
remove(payload){
  print('remove');
  LocalNotifications.removeNotification(0);
}
 not() async{

    SharedPreferences pref=await SharedPreferences.getInstance();
    String g=pref.getString("language_code")??"en";
    await LocalNotifications.createNotification(
        title: g=='ru'?"Тренировки для ног и ягодиц на 30 дней":"Trainings for butt and buttocks for 30 days",
        actions: [
          new NotificationAction(
              actionText: g=='ru'?"Отложить":"Put off",
              callbackName: "remove",
              callback: remove,
              launchesApp: false,
              payload: null),
          new NotificationAction(
              actionText: g=='ru'?"Старт":"Start",
              callback: (string) => print('ji'),
              launchesApp: true,
              payload: null)
        ],
        imageUrl: "https://cdn2.iconfinder.com/data/icons/sport-8/70/dumbbell-512.png",
        content: g=='ru'?'Пора начинать тренировку "Тренировки для ног и ягодиц на 30 дней"':'It`s time to start training in "Trainings for butt and buttocks for 30 days"',
        id: 0,
        androidSettings: new AndroidSettings(channel: channel));
    DateTime d= new DateTime.now(),dd;

    SharedPreferences prefs=await SharedPreferences.getInstance();
    int h=prefs.getInt("notification");

    //print(h);
    dd=new DateTime(d.year,d.month,d.day,(h/100).floor(),h%100,0);
    if ((h/100).floor()<d.hour || ((h/100).floor()==d.hour && h%100<=d.minute))
    {
      //print('add');
      dd=dd.add(Duration(days: 1));

    }
    print(dd);
    await AndroidAlarmManager.oneShotAt(dd, alarmId, not);
}
not1(bool p) async{

  SharedPreferences pref=await SharedPreferences.getInstance();
  String g=pref.getString("language_code")??"en";
  await LocalNotifications.createNotification(
      title: g=='ru'?"Тренировки для ног и ягодиц на 30 дней":"Trainings for butt and buttocks for 30 days",
      imageUrl: "https://cdn2.iconfinder.com/data/icons/sport-8/70/dumbbell-512.png",
      content: g=='ru'?(p?'С возвращением':"Приветствуем"):(p?"Welcome back":"Welcome"),
      id: 0,
      androidSettings: new AndroidSettings(channel: channel));

}
rateMe(context){
  List<Widget> ii=new List();


  return showDialog(context: context,
      builder: (context)
      { int stars=0;
      bool active = false;
      return StatefulBuilder(builder:(context,setState){
        ii.clear();
        for (int i=0;i<4;i++)
          ii.add(Padding(
            padding: const EdgeInsets.all(5.0),
            child: InkWell(onTap:(){setState(() {
              //print(stars);
              stars=i+1;
              active=true;
            });},child: Icon(stars>i?Icons.star:Icons.star_border,color: stars>i?Colors.yellow.shade600:Colors.grey.shade400,size: 44,)),
          ));
        ii.add(Padding(
            padding: const EdgeInsets.all(5.0),
            child: InkWell(onTap:(){launch("https://play.google.com/store/apps/details?id=mobi.devsteam.training_workout");
            },child: Icon(Icons.star_border,color: Colors.grey.shade400,size: 44,))));
        return AlertDialog(
          //title: Text("hoihoi"),
          content: Container(
            height: 360,
            width: MediaQuery.of(context).size.width-30,
            child: Column(
              children: [
                Image.asset("assets/happy.jpg",width: 90,),
                Container(margin: EdgeInsets.only(top: 15),height: 120,child: Text(AppLocalizations.of(context).translate((stars>0&&stars<4?1.toString():stars.toString())+"star"),textAlign: TextAlign.center,style: TextStyle(fontSize: 14),)),
                Row(mainAxisAlignment: MainAxisAlignment.center,children: ii,),
                Row(children: <Widget>[
                  Container(margin: EdgeInsets.only(left: 10,right: 5,top: 20),width: 205,child: Text(AppLocalizations.of(context).translate("bestt"),style: TextStyle(color: Colors.orange,fontWeight: FontWeight.bold),textAlign: TextAlign.right,)),
                  Image.asset("assets/arrow.jpg",height: 70,)
                ],)
              ],

            ),
          ),
          actions: <Widget>[
            // usually buttons at the bottom of the dialog
            Container(
              padding: EdgeInsets.only(left: 10,right: 10,bottom: 8),
              child: SizedBox(
                width: MediaQuery.of(context).size.width-50,
                child: new FlatButton(
                  color: active?Colors.orange:Colors.orange.shade200,
                  child: Padding(
                    padding: const EdgeInsets.all(3.0),
                    child: new Text(AppLocalizations.of(context).translate("rating"),style: TextStyle(color: Colors.white,fontSize: 22),),
                  ),
                  onPressed: () {
                    active?launch("https://play.google.com/store/apps/details?id=mobi.devsteam.training_workout"):null;
                  },

                ),
              ),
            ),
          ],

        );});
      }
  );


}
class InterstitialAdPage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(),
      body: Center(
        child: Text('InterstitialAd Page'),
      ),
    );
  }
}
class _MainTabsState extends State<MainTabs> with AfterInitMixin<MainTabs>{

  int selectedIndex = 0;
  int planindex=-1;
  //int stars=0;




  _MainTabsState({this.planindex}){if (planindex!=-1) selectedIndex=1;}

    static int pli;
  List<Widget> _widgetOptions;




  @override
    void initState(){

      super.initState();
      pli=planindex;
      //print("p"+pli.toString());
       _widgetOptions = <Widget>[
          day.Day(),
          Workouts(index: pli!=-1?pli:0),
         WorkoutsElementAdd(jsonindex: 6),
          AboutMe(),
        ];
      //myInterstitial.load();


    //getMessage();
     // sendAndRetrieveMessage();
    }



  @override
  void didInitState() async {
    //DateTime d=new DateTime.now();
    //d.add(Duration(minutes: 1));
    //myInterstitial = buildInterstitialAd();
    //await myInterstitial.load();
    SharedPreferences prefs=Provider.of<Data>(context,listen: false).prefs;
    print(prefs.getInt("enter"));
    if (!prefs.containsKey("enter"))
      prefs.setInt("enter", -1);
    if (prefs.getInt("enter")==9){
      prefs.setInt("enter", 0);
      async.Timer t=new async.Timer(Duration(milliseconds: 400), () {rateMe(context); });
    }
    else{
      prefs.setInt("enter", prefs.getInt("enter")+1);
    }
    //rateMe();
    //await AndroidAlarmManager.oneShot(Duration(seconds: 4), alarmId, not);

    //print("k");
    //myInterstitial = buildInterstitialAd()..load();
    //myInterstitial=buildInterstitialAd();
    //myInterstitial.load();

    //myInterstitial.load();
  }
   //List<Widget>

  void _onItemTapped(int index) {
    setState(() {
      selectedIndex = index;
    });
  }
  //////////////////////////

  @override
  Widget build(BuildContext context) {
  //myInterstitial.show();
  //return InterstitialAdPage();
    return Scaffold(

      body: Center(
        child:_widgetOptions.elementAt(selectedIndex),
      ),
      bottomNavigationBar: BottomNavigationBar(

        items:  <BottomNavigationBarItem>[
          BottomNavigationBarItem(
            icon: Icon(Icons.home),
            title:  Text(AppLocalizations.of(context).translate("tab1")),//.translate("tab1")),//// todo finalize the translation

          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.directions_run),
            title: Text(AppLocalizations.of(context).translate("tab21"),style: TextStyle(color: Colors.grey),),
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.directions_run),
            title: Text(AppLocalizations.of(context).translate("tab22")),
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.accessibility),
            title: Text(AppLocalizations.of(context).translate("tab3")),
          ),
        ],
        currentIndex: selectedIndex,
        selectedItemColor: Colors.black,
        unselectedItemColor: Colors.grey,
        //unselectedLabelStyle: TextStyle(color: Colors.grey),
        showUnselectedLabels: true,
        onTap: _onItemTapped,
      ),
    );
  }
}
