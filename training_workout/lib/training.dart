


//import 'dart:html';
import 'dart:io';
import 'dart:math';
import 'dart:ui' as ui;

import 'package:after_init/after_init.dart';
import 'package:bot_toast/bot_toast.dart';
import 'package:firebase_admob/firebase_admob.dart';
import 'package:flame/sprite.dart';
import 'package:flame/spritesheet.dart';
import 'package:flame/time.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/services.dart';
import 'package:flutter_gifimage/flutter_gifimage.dart';
//import 'package:flutter_local_notifications/flutter_local_notifications.dart';
//import 'package:flutter_local_notifications/flutter_local_notifications.dart';
import 'package:android_alarm_manager/android_alarm_manager.dart';
import 'package:image_size_getter/image_size_getter.dart';
import 'package:intl/intl.dart';

import 'package:path_provider/path_provider.dart';

import 'package:percent_indicator/percent_indicator.dart';

import 'package:flame/animation.dart' as animation; // imports the Animation class under animation.Animation
import 'package:flame/flame.dart' as flame; // imports the Flame helper class
import 'package:flame/position.dart'; // imports the Position class
//import 'package:flame/time.dart' as time;
import 'dart:async' as dartasync;

import 'package:flutter/material.dart';
import 'package:flutter_fadein/flutter_fadein.dart';
import 'package:dotted_border/dotted_border.dart';
import 'package:flutter_datetime_picker/flutter_datetime_picker.dart';

import 'package:flutter_timer/flutter_timer.dart';
import 'package:provider/provider.dart';
import 'package:share/share.dart';
import 'package:shared_preferences/shared_preferences.dart';
//import 'package:flutter_timer/flutter_timer.dart';
import 'package:path_provider/path_provider.dart';
import 'package:training_workout/aboutme.dart';

import 'main.dart';
import 'data.dart';
import 'localization.dart';
import 'data.dart';



class TrainingHeader extends SliverPersistentHeaderDelegate {
  final double minExtend;
  final double maxExtend;
  List<Color>  mainColors=[Colors.blue, Colors.purple, Colors.red];
  int lvl;
//  TrainingHeader({this.maxExtend,@required this.minExtend});
//  @override
//  Widget build(BuildContext context, double shrinkOffset, bool overlapsContent) {
//    return Text('popp');//Image.asset("assets/train1.jpg");
//  }
//
//  @override
//  double get minExtent => minExtent;
//
//  @override
//  bool shouldRebuild(SliverPersistentHeaderDelegate oldDelegate) {
//
//    return true;
//  }
//
//  @override
//  double get maxExtent => maxExtend;

  TrainingHeader({this.maxExtend,this.minExtend,this.lvl});
  final controller = FadeInController(autoStart: true);
  final controller1 = FadeInController();

  @override
  Widget build(BuildContext context, double shrinkOffset, bool overlapsContent) {
    if (shrinkOffset>70)
    {controller.fadeOut();controller1.fadeIn();}
    else{controller.fadeIn(); controller1.fadeOut();}
      return Stack(
        children: [FadeIn(curve:Curves.easeIn,controller: controller,duration: Duration(milliseconds: 300),child:
        Stack(fit: StackFit.expand,children: [
          Image.asset("assets/train"+(lvl/100).floor().toString()+".jpg",fit: BoxFit.cover,),
          AppBar(),
          Positioned(
            bottom: 35,
            left: 20,
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: <Widget>[
                Stack(

                  alignment: Alignment.bottomCenter,
                  children: <Widget>[
                    Container(
                      color: mainColors[(lvl/100).floor()-1],
                      height: 10,
                      width: 100,
                    ),
                    Text(AppLocalizations.of(context).translate('lvl')+' '+(lvl/100).floor().toString(),style: TextStyle(fontSize: 22,color: Colors.white,fontWeight: FontWeight.bold),)
                  ],
                ),
                Text(AppLocalizations.of(context).translate("day")+' '+(lvl%100).toString(),style: TextStyle(color: Colors.white,fontSize: 20),),
              ],

            ),
          ),
          Positioned(
            bottom: 0,
            child: Container(decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.only(topLeft: Radius.circular(25),topRight: Radius.circular(25))),width: MediaQuery.of(context).size.width,height: 8,),
          )])),
          FadeIn(duration: Duration(milliseconds: 300),controller: controller1,child: AppBar(backgroundColor:Colors.white,iconTheme: IconThemeData(color: Colors.black),title: Text(AppLocalizations.of(context).translate("day")+' '+(lvl%100).toString(),style: TextStyle(color: Colors.black),),))],
      );
    }


  @override
  double get maxExtent => this.maxExtend;

  @override
  double get minExtent => this.minExtend;

  @override
  bool shouldRebuild(SliverPersistentHeaderDelegate oldDelegate) {
    return true;
  }
}
class TrainingHeaderAdd extends SliverPersistentHeaderDelegate {
  final double minExtend;
  final double maxExtend;
  //List<Color>  mainColors=[Colors.blue, Colors.purple, Colors.red];
  String name;
//  TrainingHeader({this.maxExtend,@required this.minExtend});
//  @override
//  Widget build(BuildContext context, double shrinkOffset, bool overlapsContent) {
//    return Text('popp');//Image.asset("assets/train1.jpg");
//  }
//
//  @override
//  double get minExtent => minExtent;
//
//  @override
//  bool shouldRebuild(SliverPersistentHeaderDelegate oldDelegate) {
//
//    return true;
//  }
//
//  @override
//  double get maxExtent => maxExtend;

  TrainingHeaderAdd({this.maxExtend,this.minExtend,this.name});
  final controller = FadeInController(autoStart: true);
  final controller1 = FadeInController();

  @override
  Widget build(BuildContext context, double shrinkOffset, bool overlapsContent) {
    if (shrinkOffset>70)
    {controller.fadeOut();controller1.fadeIn();}
    else{controller.fadeIn(); controller1.fadeOut();}
    return Stack(
      children: [FadeIn(curve:Curves.easeIn,controller: controller,duration: Duration(milliseconds: 300),child:
      Stack(fit: StackFit.expand,children: [
        Image.asset("assets/train3.jpg",fit: BoxFit.cover,),
        AppBar(),
        Positioned(
          bottom: 35,
          left: 20,
          child:
              Text(AppLocalizations.of(context).translate(name),style: TextStyle(color: Colors.white,fontSize: 26),),
        ),
        Positioned(
          bottom: 0,
          child: Container(decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.only(topLeft: Radius.circular(25),topRight: Radius.circular(25))),width: MediaQuery.of(context).size.width,height: 8,),
        )])),
        FadeIn(duration: Duration(milliseconds: 300),controller: controller1,child: AppBar(backgroundColor:Colors.white,iconTheme: IconThemeData(color: Colors.black),title: Text(AppLocalizations.of(context).translate(name),style: TextStyle(color: Colors.black),),))],
    );
  }


  @override
  double get maxExtent => this.maxExtend;

  @override
  double get minExtent => this.minExtend;

  @override
  bool shouldRebuild(SliverPersistentHeaderDelegate oldDelegate) {
    return true;
  }
}
class Exercise extends StatefulWidget{
  String name;
  int count;
  int index;
  String image;
  Exercise({this.count,this.name,this.index,this.image});
  @override
  createState()=>new ExerciseState(name: name,count: count,index: index,image: image);
}
class ExerciseState extends State<Exercise> with TickerProviderStateMixin{
  String name;
  String image;
  int count;
  Random random =new Random();
  int index=0;

  @override
  void initState() {
    super.initState();

    //ctrl.repeat();
    //i =random.nextInt(8);
  }
  /////////

//////////////
  ExerciseState({this.name,this.count,this.index,this.image});
  GifController ctrl;
  @override
  Widget build(BuildContext context) {
    //ctrl=  GifController(vsync: this);

    //ctrl.repeat(period: Duration(seconds: ));
   // List<List<double>> m=[[342,160],[342,160],[294,160],[334,202],[112,336],[160,318],[310,258],[210,332],[136,318],[320,136],
     //                     [314,122],[150,350],[162,314],[182,334],[144,318],[320,220],[318,148],[188,264],[318,262],[302,328],
       //                   [284,150],[214,288],[316,286],[114,284],[118,290],[338,182],[244,316],[120,342],[320,314],[208,310]];

    Path customPath = Path()
      ..moveTo(0, 10)
      ..lineTo(0, 290);//m[index-1][1]+90+((name.length>31)?15:0));
    //print(image+'[');
    return Stack(
      children: [Container(
        margin: EdgeInsets.only(left: 5),
        child: DottedBorder(

          dashPattern: [5],
          strokeWidth: 1,
          customPath: (size)=>customPath,
          color: Color.fromARGB(255,207,78,61),
          child:
          Container(padding: EdgeInsets.only(left: 15),
          height: 230,

          child:  Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: <Widget>[
              Text(AppLocalizations.of(context).translate(name),style: TextStyle(fontSize: 18,fontWeight: FontWeight.bold),),
              Center(child:Container(height:150,width: MediaQuery.of(context).size.width-180,child: ExerciseAnimation(name: image,)))//Image.asset("assets/drawable-nodpi-v4/"+image+'.gif'))
            ],
        ),
            //flame.Flame.util.animationAsWidget(Position(m[index][0], m[index][1]), spritesheet.createAnimation(stepTime: 0.3)/*animation.Animation.sequenced((index+1).toString()+'.png', 2,textureWidth: m[index][0],textureHeight:m[index][1],stepTime: 0.3)*/)
          ),),
      ),
      Positioned(left: 0,top: 10,child: Container(width: 10,height: 10,decoration: BoxDecoration(color: Color.fromARGB(255,207,78,61),borderRadius: BorderRadius.all(Radius.circular(10))),)),
      Positioned(right: 5,bottom: 1,child: Container(width: 65,height: 35,child: Center(child: Text(count.toString(),style: TextStyle(fontSize: 20,color: Colors.white),)),decoration: BoxDecoration(color: Colors.grey.shade700,borderRadius: BorderRadius.only(topLeft: Radius.circular(15),bottomRight: Radius.circular(15)))),)],
    );
  }
}
class RateTraining extends StatefulWidget {
  @override
  _RateTrainingState createState() => _RateTrainingState();
}

class _RateTrainingState extends State<RateTraining> {
  int _character = 2;

  Widget build(BuildContext context) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceAround,
      children: <Widget>[
          Column(children: <Widget>[

            IconButton(icon: new Icon(Icons.thumb_down),iconSize:40,color: _character==0?Colors.red:Color.fromARGB(255, 230, 230, 230),onPressed: (){setState(() {
              _character=0;
            });},),
            Text(AppLocalizations.of(context).translate("hard")),
          ],),
        Column(children: <Widget>[
          IconButton(icon: new Icon(Icons.thumbs_up_down),iconSize:40,color: _character==1?Colors.yellow:Color.fromARGB(255, 230, 230, 230),onPressed: (){setState(() {
            _character=1;
          });},),
          Text(AppLocalizations.of(context).translate("norm")),

        ],),
        Column(children: <Widget>[
          IconButton(icon: new Icon(Icons.thumb_up),iconSize:40,color: _character==2?Colors.green:Color.fromARGB(255, 230, 230, 230),onPressed: (){setState(() {
            _character=2;
          });},),
          Text(AppLocalizations.of(context).translate("easy")),

        ],),
      ],
    );
  }
}

class ExerciseEnd extends StatefulWidget {
  int ex;double ccal;Duration time;int level;String name;
  ExerciseEnd({this.ex,this.ccal,this.time,this.level,this.name});
  @override
  _ExerciseEndState createState() => _ExerciseEndState(ex:ex,ccal: ccal,time:time,level:level,name: name);
}
class MyScrollBehavior extends ScrollBehavior {
  @override
  Widget buildViewportChrome(
      BuildContext context, Widget child, AxisDirection axisDirection) {
    return child;
  }
}
class _ExerciseEndState extends State<ExerciseEnd> with AfterInitMixin<ExerciseEnd>{
  int ex;
  double ccal;
  Duration time;
  int level;
  String name;
  SharedPreferences prefs;
  _ExerciseEndState({this.ex,this.ccal,this.time,this.level,this.name});
  Future<String> get _localPath async {
    final directory = await getApplicationDocumentsDirectory();
    // For your reference print the AppDoc directory
    //print(directory.path);
    return directory.path;
  }
  Future<File> get _localFile async {
    final path = await _localPath;
    return File('$path/data.txt');
  }
  Future<File> writeContent(DateTime time) async {
    final file = await _localFile;
    // Write the file
    //DateTime.now().w
    //return file.writeAsString("2 6 2020 110 5 7\n");
    if (name==null) name="no_name";
    //print(time.day.toString()+' '+time.month.toString()+' '+time.year.toString()+' '+level.toString()+" "+ccal.round().toString()+' '+this.time.inMinutes.toString()+' '+name);
    return file.writeAsString(time.day.toString()+' '+time.month.toString()+' '+time.year.toString()+' '+level.toString()+" "+ccal.round().toString()+' '+this.time.inMinutes.toString()+' '+name+'\n',mode: FileMode.append);
  }
  InterstitialAd myInterstitial;

  InterstitialAd buildInterstitialAd() {
    if (Platform.isAndroid)
    return InterstitialAd(
      adUnitId: "ca-app-pub-8323348147242911/6032390531",
      listener: (MobileAdEvent event) {
        if (event == MobileAdEvent.failedToLoad) {
          myInterstitial..load();
        } else if (event == MobileAdEvent.closed) {
          myInterstitial = buildInterstitialAd()..load();
        }
        print(event);
      },
    ); else if (Platform.isIOS)
      return InterstitialAd(
        adUnitId: "ca-app-pub-8323348147242911/2574515342",
        listener: (MobileAdEvent event) {
          if (event == MobileAdEvent.failedToLoad) {
            myInterstitial..load();
          } else if (event == MobileAdEvent.closed) {
            myInterstitial = buildInterstitialAd()..load();
          }
          print(event);
        },
      );
  }

  void showInterstitialAd() {
    myInterstitial..show();
  }
  @override
  void initState() {
    myInterstitial = buildInterstitialAd()..load();

    //(level/100).floor()!=4?
    writeContent(DateTime.now());

    super.initState();
  }
  @override
  void dispose() {
    myInterstitial.dispose();

    super.dispose();
  }
  @override
  void didInitState() {
    Provider.of<Data>(context).readcontent();
    prefs=Provider.of<Data>(context).prefs;
    hour=(prefs.getInt("notification")/100).floor()%12==0?12:(prefs.getInt("notification")/100).floor()%12;
    minute=(prefs.getInt("notification")%100);
    pm=(prefs.getInt("notification")/100).floor()>12;
    //dartasync.Timer t=new dartasync.Timer(Duration(seconds: 5), () {showInterstitialAd();});
    showInterstitialAd();
    //fetchnotif();
  }

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
                                },scrollController: new FixedExtentScrollController(initialItem:prefs.getInt("notification")%100),)
                            //backgroundColor: Colors.blue,


                          ),
                          Container(
                              width: 70,
                              //child: Cupert,
                              child: CupertinoPicker(children: [Center(child: Text("am")),Center(child: Text("pm"))],itemExtent: 40,
                                highlighterBorder: Color.fromARGB(255, 207, 78, 61),highlighterBorderWidth: 1.5,onSelectedItemChanged: (value){
                                  pm=(value==1);
                                },scrollController: new FixedExtentScrollController(initialItem:  ((((prefs.getInt("notification")/100).floor())>12)?1:0)),)
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
                            onPressed: () async{
                              int b=hour*100+(pm?1:0)*1200+minute;
                              //print(b);
                              //print(hour+(pm?1:0)*12+minute);
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
                              Provider.of<Data>(context,listen: false).prefs.setInt("notification", b);
                              //print(Provider.of<Data>(context,listen: false).plugin);
                              //daily(Provider.of<Data>(context,listen: false).plugin, hour+(pm?1:0)*12, minute);
                              Navigator.of(context).pop();BotToast.showSimpleNotification(title: AppLocalizations.of(context).translate("saved"),closeIcon: Icon(Icons.check,color: Colors.green,));},textColor: Colors.white,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0)
                            )
                        ),

                      ),
                    ],
                    )]));
        }
    );

  }
  int notif;
  int hour;
  int minute;
  bool pm;
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
//  }

  @override
  Widget build(BuildContext context) {
    //print(level);
    return WillPopScope(
      onWillPop: (){Navigator.pop(context,true);},
      child: SafeArea(
          child: Scaffold(
            body: Stack(
              children: <Widget>[
               Container(width: MediaQuery.of(context).size.width,height: MediaQuery.of(context).size.height,color: Color.fromARGB(255, 230, 230, 230),)
              ,Image.asset("assets/end.jpg"),
                Transform.translate(offset: Offset(-24,0),child: Container(margin: EdgeInsets.only(top: 250),width: MediaQuery.of(context).size.width+90,height: 100,color: Color.fromARGB(255, 230, 230, 230),transform: Matrix4.rotationZ(-0.1))),
                ScrollConfiguration(
                  behavior: MyScrollBehavior(),
                  child: ListView(
                    //crossAxisAlignment: CrossAxisAlignment.start,

                    children: <Widget>[
                      Container(

                        width: 200,
                        margin: EdgeInsets.only(top: 80,left: 30,bottom: 20),
                        child:
                         Column(
                           crossAxisAlignment: CrossAxisAlignment.start,
                           children: <Widget>[
                             Text(AppLocalizations.of(context).translate("done"),style: TextStyle(color: Colors.white,fontWeight: FontWeight.bold,fontSize: 28),)
                                 ,
                             Padding(
                               padding: const EdgeInsets.only(top:8.0),
                               child: (level/100).floor()!=4?Text(AppLocalizations.of(context).translate("day")+(level%10).toString()+' - '+AppLocalizations.of(context).translate("lvl")+' '+(level/100).floor().toString(),style: TextStyle(color: Colors.white,fontSize: 16),)
                                   :Text(AppLocalizations.of(context).translate(name),style: TextStyle(color: Colors.white,fontSize: 20,fontWeight: FontWeight.bold),),
                             )
                           ],
                         )
                      ),
                      Container(margin: EdgeInsets.only(left: 10,right: 10,bottom: 20,top: 50),padding: EdgeInsets.all(8),width: MediaQuery.of(context).size.width,
                      decoration: BoxDecoration(color:Colors.white,borderRadius: BorderRadius.all(Radius.circular(20))),child: Column( children: <Widget>[
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: Row(mainAxisAlignment: MainAxisAlignment.spaceAround,
                              children: <Widget>[

                              Column(children: <Widget>[
                                Text(AppLocalizations.of(context).translate("exercises")),
                                Text(ex.toString(),style: TextStyle(color: Color.fromARGB(255,207,78,61),fontSize: 20,fontWeight: FontWeight.bold),),
                              ],),
                            Column(children: <Widget>[
                              Text(AppLocalizations.of(context).translate("cal")),
                              Text(((ccal).round()).toString(),style: TextStyle(color: Color.fromARGB(255,207,78,61),fontSize: 20,fontWeight: FontWeight.bold),),
                            ],),
                            Column(children: <Widget>[
                              Text(AppLocalizations.of(context).translate("dur")),
                              Text(((time.inMinutes/10).floor()==0?"0":"")+time.inMinutes.toString()+":"+((time.inSeconds%60/10).floor()==0?'0':"")+(time.inSeconds%60).toString(),style: TextStyle(color: Color.fromARGB(255,207,78,61),fontSize: 20,fontWeight: FontWeight.bold),),
                            ],)
                          ]),
                        ),
                           SizedBox(
                            width: 300,
                            height: 45,
                            child: FlatButton(child: Row(mainAxisAlignment: MainAxisAlignment.center,children: <Widget>[Container(margin: EdgeInsets.only(right: 10),child: Icon(Icons.share)),Text(AppLocalizations.of(context).translate("share"),style: TextStyle(color: Colors.white,fontSize: 17,fontWeight: FontWeight.bold),)],),color: Color.fromARGB(255,207,78,61),onPressed: (){Share.share(AppLocalizations.of(context).translate("shared"));},textColor: Colors.white,
                                shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(30.0))),
                          ),
                         Padding(
                           padding: const EdgeInsets.only(top: 15.0,bottom: 10),
                           child: SizedBox(
                            width: 300,
                            height: 45,
                            child: FlatButton(child: Row(mainAxisAlignment: MainAxisAlignment.center,children: [Container(margin: EdgeInsets.only(right: 10),child: Icon(Icons.done)),Text(AppLocalizations.of(context).translate("finish"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 17),)]),color: Color.fromARGB(255, 220, 220, 220),onPressed: (){Navigator.pop(context); BotToast.showSimpleNotification(title:AppLocalizations.of(context).translate("dowell"),closeIcon: Icon(Icons.check_circle,color: Colors.green,size: 24));},textColor: Colors.black,
                                shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(30.0))),
                        ),
                         ),
                      ],),),
                      Container(margin: EdgeInsets.all(10),padding: EdgeInsets.all(15),decoration: BoxDecoration(color:Colors.white,borderRadius: BorderRadius.all(Radius.circular(20))),
                        child: Column( crossAxisAlignment: CrossAxisAlignment.start,children: <Widget>[
                          Container(margin: EdgeInsets.only(bottom: 10),child: Text(AppLocalizations.of(context).translate("howfeel"),style: TextStyle(fontWeight: FontWeight.w700,fontSize: 20),)),
                          Text(AppLocalizations.of(context).translate("yourfeed"),style: TextStyle(color: Colors.grey),),
                          RateTraining(),


                        ],),),
                      Container(margin: EdgeInsets.all(10),padding: EdgeInsets.all(8),decoration: BoxDecoration(color:Colors.white,borderRadius: BorderRadius.all(Radius.circular(20))),
                        child: SizedBox(
                        width: MediaQuery.of(context).size.width-20,
                        child: FlatButton(child: Column(crossAxisAlignment: CrossAxisAlignment.start,
                          children: <Widget>[
                            Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[Text(AppLocalizations.of(context).translate("notif"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 20),),
                            Row(
                              children: <Widget>[
                                Text(((hour/10).floor()==0?"0":"")+hour.toString()+':'+((minute/10).floor()==0?"0":"")+minute.toString()+' '+(pm?"pm":"am")+' '),
                                Icon(Icons.border_color,color: Colors.grey.shade300,size: 16,)
                              ],
                            ),],),
                            Text(AppLocalizations.of(context).translate("choosetime")),
                          ],
                        ),onPressed: ()async {
                          //DateTime a= await DatePicker.showTimePicker(context,showSecondsColumn: false);
                          //if (a!=null){
                          //int b=a.hour*100+a.minute;
                          //Provider.of<Data>(context,listen: false).prefs.setInt("notification", b);}
                          myTimePicker(context);

                          //fetchnotif();
                          //daily(Provider.of<Data>(context,listen: false).plugin, hour+(pm?12:0), minute);
                        },),),),

                    ],
                  ),
                ),
              ],
            ),
          ),

      ),
    );
  }
}
class Paused{
  bool isPaused,isFirst,isBreak;
  DateTime timenow;
   String name;
  double ccal;
  bool circle;
  Paused({this.isPaused=false,this.isBreak=false,this.isFirst=true,this.circle=false}){
    this.timenow=DateTime.now();
    ccal=0;
  }
  circl(){
    this.circle=true;
  }
  setName(String name){
    this.name=name;
  }
  trigger(){
    isPaused=!isPaused;
  }
  triggerFirst(){
    isFirst=false;
  }
  triggerBreak(){
    isBreak=!isBreak;
  }
}

class ExerciseAnimation extends StatefulWidget {
  final int index;
  Paused paused;
  String name;
  ExerciseAnimation({this.index,this.paused,this.name});
  @override
  _ExerciseAnimationState createState() => _ExerciseAnimationState(index: index,paused: paused,name: name);
}


class _ExerciseAnimationState extends State<ExerciseAnimation> {
  //List<int> ex;
  final int index;
  String name;
  //bool isPaused;
 Paused paused;
  //List<List<double>> m=[[342,160],[342,160],[294,160],[334,202],[112,336],[160,318],[310,258],[210,332],[136,318],[320,136],[314,122]];
  //List<List<double>> m=[[342,160],[342,160],[294,160],[334,202],[112,336],[160,318],[310,258],[210,332],[136,318],[320,136],
  //  [314,122],[150,350],[162,314],[182,334],[134,318],[320,220],[318,148],[188,264],[318,262],[302,328],
  //  [284,150],[214,288],[316,286],[114,284],[118,290],[338,182],[244,316],[120,342],[320,314],[208,310]];
  //List<List<int>> mm=[[2,4],[2,4],[2,4],[2,6],[6,2],[7,2],[2,6],[7,2],[6,3],[3,4],
   //                   [3,4],[2,1],[7,2],[5,3],[4,2],[3,4],[2,4],[5,2],[2,11],[7,2],
     //                 [2,7],[4,4],[4,5],[7,2],[7,2],[4,4],[4,3],[5,2],[2,5],[5,2]];

  _ExerciseAnimationState({this.index,this.paused,this.name
  }){
    if (paused==null)
      paused=new Paused();
  }

  @override
  Widget build(BuildContext context) {
    //isPaused=prefs.getBool("pause")??false;

//    final spritesheet = MySpriteSheet(
//
//      imageName: (index+1).toString()+'.png',
//      columns: mm[index][0],
//      rows: mm[index][1],
//      textureWidth: m[index][0].round(),
//      textureHeight: m[index][1].round(),
//
//    );
//    spritesheet.load();
//    return
//             Container(child: flame.Flame.util.animationAsWidget(Position(m[index][0], m[index][1]), spritesheet.createAnimation(stepTime: paused.isPaused?100000:0.3,),));
   // print(name);
    return Image.asset("assets/drawable-nodpi-v4/"+name+'.gif');
  }
}

class ExesFull extends StatefulWidget {
  int index;
  int level;
  final data;
  String name;
  bool circle;
  //double ccal;
  //Paused paused;
  ExesFull({this.level,this.index,this.data,this.name,this.circle=false});
  @override
  _ExesFullState createState() => _ExesFullState(level:level,index:index,data:data,name: name,circle: circle);
}

class _ExesFullState extends State<ExesFull> {
  int index;
  int level;
  String name;
  bool circle;
  final data;
  Paused paused=new Paused();

  _ExesFullState({this.level,this.index,this.data,this.name,this.circle=false});
  @override
  void initState() {

    super.initState();
    paused.setName(name);
    if (circle) paused.circl();
  }
  @override
  Widget build(BuildContext context) {

    return BreakScreen(data: data,level:level,index:index,paused:paused,);
  }
}


class MainEx extends StatefulWidget {
  int index;   ///////
  final data;
  int level;
  //double ccal;
  Paused paused;
  //isFirst=true;
  MainEx({this.index,this.level,this.data,this.paused});
  @override
  _MainExState createState() => _MainExState(index: index, level: level, data: data,paused: paused,);
}
class _MainExState extends State<MainEx> with AfterInitMixin<MainEx>{
  //bool isPause;///////
  int index;   ///////
  final data;
  int level;
  Paused paused;
  SharedPreferences prefs;
  //double ccal;

  _MainExState({this.index,this.level,this.data,this.paused,});
@override
  void didInitState() async{

  await Provider.of<Data>(context,listen: false).pool.play(Provider.of<Data>(context).find("go"));
  //print("go");
  prefs=Provider.of<Data>(context,listen: false).prefs;
  }
  @override
  Widget build(BuildContext context) {
//  dartasync.Timer tt=new dartasync.Timer(Duration(seconds: 3), () { setState(() {
//
//  });});
  //print(data[index]);
    return SafeArea(
        child: Scaffold(
        body:  Stack(
          children: [Column(
            children: [Container(height: MediaQuery.of(context).size.height/2,width: MediaQuery.of(context).size.width,color: Colors.white,child: Center(child:
              ExerciseAnimation(paused: paused,name: data[index]['img_key'].toString(),))),
              ExOngoing(index: index,level: level,data: data,
              paused: paused,callback: (){setState(() {

              });}),
            ]
            ),
            (index+1<data.length && paused.circle)?Positioned(
              top: 30,
              right: 30,
              child: Container(height: 100,width: 100,decoration: BoxDecoration(color: Colors.grey.shade300,shape: BoxShape.circle,
                  image: new DecorationImage(
                      //fit: BoxFit.fill,
                      image: new AssetImage("assets/drawable-nodpi-v4/"+data[index+1]['img_key'].toString()+'.gif'
                          )
                  )),)
            ):Text(''),
            Positioned(top: 20,left: 20,child: Container(
              width: 100,
              padding: EdgeInsets.only(top: 5,bottom: 5,left: 10),
              decoration: BoxDecoration(color: Colors.grey.shade300,borderRadius: BorderRadius.all(Radius.circular(20))),
              child: Row(children: <Widget>[
                Container(margin: EdgeInsets.only(right: 5),child: Icon(Icons.whatshot,color: Colors.white,)),
                Text((((paused.ccal*100).round())/100).toString(),style: TextStyle(fontSize: 18,color: Colors.white),)]
                ,),
            ),),
          Positioned(bottom:MediaQuery.of(context).size.height/2-20, right: 10, child: Row(
            children: <Widget>[
              Container(width: 55,child: FlatButton(onPressed:(){},child: Icon(Icons.thumb_up,color: Colors.white,),color: Colors.grey.shade300,shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(20))),)),

              Container(margin: EdgeInsets.only(left: 10),width:55,child: FlatButton(onPressed:(){},child: Icon(Icons.thumb_down,color: Colors.white,),color: Colors.grey.shade300,shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(20))))),
            ],
          ),),
          paused.isPaused?Positioned(top: 0,child:
            Container(color: Color.fromARGB(255, 207, 78, 61),width: MediaQuery.of(context).size.width,height: MediaQuery.of(context).size.height/2,),):Text(''),
          paused.isPaused?Container(width: MediaQuery.of(context).size.width,height: MediaQuery.of(context).size.height-MediaQuery.of(context).padding.top,color: Color.fromARGB(250, 227, 89, 76),child:
            Column(crossAxisAlignment: CrossAxisAlignment.start,
              //mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[

              Container(margin: EdgeInsets.only(left: 20,top: MediaQuery.of(context).size.height/2-200),child: Text(AppLocalizations.of(context).translate("pause"),style: TextStyle(color: Colors.white,fontSize: 28,fontWeight: FontWeight.bold),)),
                Container(
                  margin: EdgeInsets.only(top:40,bottom: 20),
                  alignment: Alignment.center,
                  child: SizedBox(
                    height: 70,

                    width: MediaQuery.of(context).size.width-30,
                    child: FlatButton(padding:EdgeInsets.all(15),child: Align(alignment: Alignment.centerLeft,child: Text(AppLocalizations.of(context).translate("restart"),style: TextStyle(color: Colors.white,fontSize: 20))),color:Color.fromARGB(255,254,125,110),onPressed: (){
                      prefs.setInt("level"+level.toString(), (prefs.getInt("level"+level.toString())/100).floor()*100);
                      Navigator.pushReplacement(context,new MaterialPageRoute(builder: (context)=>BreakScreen(data: data,level:level,index:0,paused:new Paused(),)));
                    },shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(10)))),
                  ),
                ),
                Container(
                  margin: EdgeInsets.only(top:0,bottom: 20),
                  alignment: Alignment.center,
                  child: SizedBox(
                    height: 70,
                    width: MediaQuery.of(context).size.width-30,
                    child: FlatButton(padding:EdgeInsets.all(15),child: Align(alignment: Alignment.centerLeft,child: Text(AppLocalizations.of(context).translate("exit"),style: TextStyle(color: Colors.white,fontSize: 20))),color:Color.fromARGB(255,254,125,110),onPressed: (){Navigator.pop(context);},shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(10))),
                ),
                  ),
                ),
              Container(
                alignment: Alignment.center,
                child: SizedBox(
                    height: 70,
                  width: MediaQuery.of(context).size.width-30,
                  child: FlatButton(padding:EdgeInsets.all(15),child: Align(alignment: Alignment.centerLeft,child: Text(AppLocalizations.of(context).translate("continue"),style: TextStyle(color: Color.fromARGB(255,227,85,67),fontSize: 20),)),color:Colors.white,onPressed: (){

                    //prefs.setBool("pause", prefs.getBool("pause"));
                    paused.trigger();
                    setState(() {
                    //isPause=!isPause;

                  });},shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(10)))),
                ),
              )
            ],),):Text(''),


          ],
        )
        )

    );
  }
}
class BreakScreen extends StatefulWidget {

  int index;
  int level;
  final data;
  //double ccal;
  Paused paused;
  BreakScreen({this.index,this.data,this.level,this.paused});
  @override
  _BreakScreenState createState() => _BreakScreenState(index: index,data: data,level: level,paused: paused);
}
playnumber(n,context)async{
  await Provider.of<Data>(context,listen: false).pool.play(Provider.of<Data>(context,listen: false).find("number_"+n.toString()));
}
class _BreakScreenState extends State<BreakScreen> with AfterInitMixin<BreakScreen>{
 int time;
  int index;
  int level;
  final data;
  //double ccal;
  Paused paused;
  dartasync.Timer timer;
  _BreakScreenState({this.index,this.data,this.level,this.paused}){
    time=paused.isFirst?10:30;
    //(index);
  }
  @override
  void didInitState() async{
    if ( !paused.isFirst) await Provider.of<Data>(context,listen: false).pool.play(Provider.of<Data>(context).find("rest"));

    timer=new dartasync.Timer.periodic(Duration(seconds: 1), (timer) {
      if (time==4){
         playnumber(3, context);
      }
      if (time==3){
        playnumber(2, context);
      }
      if (time==2){
        playnumber(1, context);
      }
      if (time==1){
        timer.cancel();
        Navigator.pushReplacement(context, new MaterialPageRoute(
            builder: (context) =>
                MainEx(index: index ,
                  //ccal: ccal,
                  data: data,
                  level: level,
                  paused: paused,
                )));
      }
      else
      setState(() {
        time--;
      });
    });
  }

  Future<bool> _onBackPressed() {
    //if (!isPaused)

    return showDialog(
      context: context,
      builder: (context) => new AlertDialog(
        title: new Text(AppLocalizations.of(context).translate("rusure")),
        content: new Text(AppLocalizations.of(context).translate("duexit")),
        actions: <Widget>[
            SizedBox(
              width: 100,
              child: new FlatButton(
                onPressed: () => Navigator.of(context).pop(false),
                child: Text(AppLocalizations.of(context).translate("no"),style: TextStyle(color: Colors.white),),
                color: Colors.redAccent,
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(20))),
              ),
            ),
            SizedBox(
              width: 100,
              child: new FlatButton(
                onPressed: ()  {timer.cancel(); return Navigator.of(context).pop(true);} ,
                child: Text(AppLocalizations.of(context).translate("yes"),style: TextStyle(color: Colors.black),),
                color: Colors.grey.shade300,
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(20))),
              ),
            ),

          ],

      ),
    ) ??
        false;
  }
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: WillPopScope(
        onWillPop: _onBackPressed,
        child: Column(
          children: <Widget>[
            Container(
              padding: EdgeInsets.only(bottom: (MediaQuery.of(context).size.height-240-280)/2),
              width: MediaQuery.of(context).size.width,
              height: MediaQuery.of(context).size.height-140,
              color: Color.fromARGB(240, 207, 78, 61),
              child: Column(mainAxisAlignment: MainAxisAlignment.end,children: <Widget>[
                Text(AppLocalizations.of(context).translate("prepare").toUpperCase(),style: TextStyle(color: Colors.white,fontSize: 24,fontWeight: FontWeight.bold),),
                Padding(
                  padding: const EdgeInsets.all(3.0),
                  child: Text((((time/600).floor()==0)?"0":"")+((time/60).floor().toString())+":"+((((time%60)/10).floor()==0)?'0':'')+((time%60).toString()),style: TextStyle(color: Colors.white,fontSize: 62,fontWeight: FontWeight.bold)),
                )
                ,Padding(
                  padding: const EdgeInsets.only(top:10.0),
                  child: Row(mainAxisAlignment: MainAxisAlignment.center,children: <Widget>[
                    Padding(
                      padding: const EdgeInsets.only(right: 10.0),
                      child: FlatButton(child: Text("+20"+AppLocalizations.of(context).translate("sec"),style: TextStyle(color: Colors.white,fontSize: 16,fontWeight: FontWeight.bold),),color: Color.fromARGB(255,220,110,95),onPressed: (){setState(() {
                        time+=20;});},  shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(28.0)),),
                    ),

                        Padding(
                          padding: const EdgeInsets.only(left:20.0),
                          child: FlatButton(child: Text(AppLocalizations.of(context).translate("skip"),style: TextStyle(fontSize: 16,fontWeight:FontWeight.bold,color: Color.fromARGB(240, 230, 40, 40)),),color: Colors.white,onPressed: (){setState(() {
                            timer.cancel();
                            Navigator.pushReplacement(context, new MaterialPageRoute(
                                builder: (context) =>
                                    MainEx(index: index ,
                                      //ccal: ccal,
                                      data: data,
                                      level: level,
                                      paused: paused,
                                    )));});}, shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(28.0))),
                        )
                  ],),
                )
              ],),
            ),
            Container(
              width: MediaQuery.of(context).size.width,
              height: 140,
              child: Column(crossAxisAlignment: CrossAxisAlignment.start,mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: <Widget>[
                  Container(height: 5,color: Color.fromARGB(255,207,78,61),width: MediaQuery.of(context).size.width*(index+1)/data.length,),
                  Container(
                    height: 135,
                    width: MediaQuery.of(context).size.width,
                    color: Colors.white,
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: <Widget>[
                        Column(crossAxisAlignment:CrossAxisAlignment.start,mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[

                          Padding(padding: EdgeInsets.only(left:10,top: 15),child: Row(
                            children: <Widget>[
                              Text(AppLocalizations.of(context).translate("next").toUpperCase()+' ',style: TextStyle(fontSize: 18,color: Colors.grey),),
                              Text((index+1).toString()+'/'+data.length.toString(),style: TextStyle(fontSize: 18,color: Color.fromARGB(255,207,78,61))),

                            ],
                          ),),
                          Padding(
                            padding: const EdgeInsets.only(left:10.0),
                            child: Container(width:250,child: Text(AppLocalizations.of(context).translate(data[index]["name_key"]??data[index]['img_key'].toString()),style: TextStyle(fontSize: 16,fontWeight: FontWeight.bold))),
                          ),
                          Padding(
                            padding: const EdgeInsets.only(left:10.0,bottom: 10),
                            child: Text((data[index]["duration"]/1000).round().toString()+" "+AppLocalizations.of(context).translate("sec"),style: TextStyle(fontSize: 16)),
                          )
                        ],),
                        Image.asset("assets/drawable-nodpi-v4/"+data[index]["img_key"].toString()+".gif",height: 120,width: 120,)
                      ],
                    ),
                  ),
                ],
              ),
            )
          ],
        ),
      ),
    );
  }
}


class ExOngoing extends StatefulWidget {
  int level;int index;
  Function callback;
  Paused paused;
  final data;
  //double ccal;
  ExOngoing({this.data,this.level,this.index,this.paused,this.callback});
  @override
  _ExOngoingState createState() => _ExOngoingState(paused: paused,data: data,level: level,index: index,callback: callback);
}

class _ExOngoingState extends State<ExOngoing> with AfterInitMixin<ExOngoing>{
  double starttime,time=10;
  Paused paused;
  Function callback;
  final data;
  int index;
  int level;
  bool played1=false,played2=false,played3=false;
  //bool isBreak=false,isFirst=true;
  dartasync.Timer timer;
  SharedPreferences pref;
  //double ccal;
  //bool firstStart=true;

  _ExOngoingState({this.data,this.level,this.index,this.paused,this.callback}){
    time=data[index]['duration']/1000.0;
    starttime=time;
  }
  int writelvl;

  @override
  void didInitState(){
    pref=Provider.of<Data>(context).prefs;
    nextTimer();
    paused.triggerFirst();
    writelvl=level*100+(pref.getInt("level"+level.toString())/100).round();
  }

  void nextTimer() {
    //print("update");


    timer= dartasync.Timer.periodic(Duration(milliseconds: 10 ),(timer){
      if (time.ceil()==3 && !played1){
        playnumber(3, context);
        played1=true;
      }
      if (time.ceil()==2 && !played2){
        playnumber(2, context);
        played2=true;
      }
      if (time.ceil()==1 && !played3){
        playnumber(1, context);
        played3=true;
      }
      if (time.ceil()==0){
        timer.cancel();


         if (index+1==data.length){
            timer.cancel();
           Navigator.pushReplacement(context,new MaterialPageRoute(builder: (context)=>ExerciseEnd(name: paused.name,ex: index+1,ccal: paused.ccal,time: DateTime.now().difference(paused.timenow),level: /*level*100+*/(writelvl)/*/100*/)));
            pref.setInt("level"+level.toString(), (pref.getInt("level"+level.toString())/100).ceil()*100);

            return;
         }else {
           //index = index + 1;

           //callback();

           pref.setInt("level" + level.toString(),
               pref.getInt("level" + level.toString()) + 1);
           Navigator.pushReplacement(context, new MaterialPageRoute(
               builder: (context) =>
                   BreakScreen(index: index + 1,
                       //ccal: ccal,
                       data: data,
                       level: level,
                   paused: paused,
                   )));
           return;
         }

      }else  if (time.ceil()!=(time-0.01).ceil()){
        setState(() {
          time=time-0.01;
          paused.ccal+=4.4*pref.getInt("weight")/3600;
          callback();
        });}
      else{
        setState(() {
          time-=0.01;
        });
      }

    });
  }
  Future<bool> _onBackPressed() {
    //if (!isPaused)
    if (!paused.isPaused)
    pause();//
    return showDialog(
      context: context,
      builder: (context) => new AlertDialog(
        title: new Text(AppLocalizations.of(context).translate("rusure")),
        content: new Text(AppLocalizations.of(context).translate("duexit")),
        actions: <Widget>[
          SizedBox(
            width: 100,
            child: new FlatButton(
              onPressed: () => Navigator.of(context).pop(false),
              child: Text(AppLocalizations.of(context).translate("no"),style: TextStyle(color: Colors.white),),
              color: Colors.redAccent,
              shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(20))),
            ),
          ),
          SizedBox(
            width: 100,
            child: new FlatButton(
              onPressed: ()  {timer.cancel(); return Navigator.of(context).pop(true);} ,
              child: Text(AppLocalizations.of(context).translate("yes"),style: TextStyle(color: Colors.black),),
              color: Colors.grey.shade300,
              shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(20))),
            ),
          ),

        ],
      ),
    ) ??
        false;
  }
  pause(){

    //isPaused
    paused.isPaused?nextTimer():timer.cancel();
    //isPaused=!isPaused;
    paused.trigger();
    callback();
  }
  @override
  void didUpdateWidget(ExOngoing oldWidget) {
    !paused.isPaused&&!timer.isActive?nextTimer():{};
    super.didUpdateWidget(oldWidget);
  }
  @override
  Widget build(BuildContext context) {
    var a=(starttime-time).floor();
    return WillPopScope(
        onWillPop: _onBackPressed,
        child:Expanded(
              flex: 1,
              child: Stack(
                children: [/*Container(width: MediaQuery.of(context).size.width,height: MediaQuery.of(context).size.height,
                  color: Color.fromARGB(200, 230, 0, 0),),*/
                  Container(
                child: Padding(
                padding: const EdgeInsets.only(top: 58.0),
                child: Column(children: <Widget>[
                  Text(AppLocalizations.of(context).translate(data[index]["name_key"]??data[index]['img_key'].toString()).toUpperCase(),style: TextStyle(color: Colors.black,fontSize: 22,fontWeight: FontWeight.bold,),textAlign: TextAlign.center,),

                  Expanded(
                    flex: 1,

                    //margin: const EdgeInsets.only(top: 58.0),
                    child:
                      Column(
                        mainAxisAlignment: MainAxisAlignment.center ,
                          children: <Widget>[
                            Container(
                              child: Text((((a/60)>9)?'':'0')+(a/60).floor().toString() +':'+((a%60>9)?'':'0')+(a%60).toString()+'/'+(((starttime/60)>9)?'':'0')+(starttime/60).floor().toString() +':'+((starttime%60>9)?'':'0')+(starttime%60).round().toString(),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 36),),

                            ),



                                Container(
                                 margin: EdgeInsets.only(top:30,bottom: 50),
                                 child:
                                     Stack(
                                       children: <Widget>[
                                          //LinearPercentIndicator()
                                          Positioned(
                                            left: MediaQuery.of(context).size.width/2-120,

                                               child: ClipRRect(
                                                 borderRadius: BorderRadius.all(Radius.circular(28)),
                                                 child: Container(
                                                   height: 45,
                                                   width: 240,
                                                   child: LinearProgressIndicator(
                                                     value: (starttime-time)/starttime,
                                                     valueColor: AlwaysStoppedAnimation<Color>( Color.fromARGB(255, 207, 78, 67)),
                                                     backgroundColor: Color.fromARGB(255, 227, 100, 80),
                                                   ),
                                                 ),
                                               ),

                                          ),
//                                         child: LinearPercentIndicator(
//                                           lineHeight: 45,
//                                           width: 240,
//                                           percent: (starttime-time)/starttime,
//                                           backgroundColor: Color.fromARGB(255, 227, 100, 80),
//                                           progressColor: Color.fromARGB(255, 207, 78, 67),
//                                           linearStrokeCap: LinearStrokeCap.roundAll,
//
//                                         ),
                                         Center(
                                           child: SizedBox(
                                             //margin: EdgeInsets.all(8),
                                             width: 240,
                                             height: 45,
                                             child: FlatButton(child: Row(mainAxisAlignment: MainAxisAlignment.center,children: [Icon(Icons.pause,color: Colors.white,size: 28,),Text((AppLocalizations.of(context).translate("pause")).toUpperCase(),style: TextStyle(fontSize: 20),)]),color: Colors.transparent,
                                                 onPressed: (){pause();
                                                 //pref.setBool("pause", !(pref.getBool("pause")??false));

                                                 setState(() {

                                                 });},textColor: Colors.white,
                                                 shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(28.0))),
                                           ),
                                         ),
                                       ],
                                     ),
                             ),

                          ],
                        ),
                        )]))),

                Positioned(
                  bottom: 0,
                  child: Row(crossAxisAlignment: CrossAxisAlignment.end,mainAxisAlignment: MainAxisAlignment.center,children:[
                    Container(

                      padding: EdgeInsets.all(8),
                      width: MediaQuery.of(context).size.width/2,
                      child: FlatButton(child: Row(
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: <Widget>[
                          Icon(Icons.fast_rewind,size: 30,color:  Colors.grey,),
                          Text(AppLocalizations.of(context).translate("prev"),style: TextStyle(fontSize: 16,color: Colors.grey),),
                        ],
                      ),onPressed: (){
                        timer.cancel();
                        Navigator.pushReplacement(context,new MaterialPageRoute(builder: (context)=>BreakScreen(data: data,level:level,index:index==0?0:index-1,paused:index-1==0?new Paused():paused,)));
                      }),
                    ),
                    Container(
                        width: MediaQuery.of(context).size.width/2,
                        margin: EdgeInsets.all(8),
                        child: FlatButton(child: Row(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: <Widget>[
                            Icon(Icons.fast_forward,size: 30,color: Colors.grey),
                            Text(AppLocalizations.of(context).translate("next"),style: TextStyle(fontSize: 16,color: Colors.grey),),
                          ],
                        ),onPressed: (){
                          timer.cancel();

                          if (index+1==data.length){
                            Navigator.pushReplacement(context,new MaterialPageRoute(builder: (context)=>ExerciseEnd(name:paused.name,ex: index+1,ccal: paused.ccal,time: DateTime.now().difference(paused.timenow),level: /*level*100+*/writelvl)));
                            pref.setInt("level"+level.toString(), (pref.getInt("level"+level.toString())/100).ceil()*100);
                            return;
                          }else {
                            //index = index + 1;
                            if (/*isPaused*/paused.isPaused){pause();     //pref.setBool("pause", !(pref.get("pause")??false));
                            }
                            //callback();

                            pref.setInt("level" + level.toString(),
                                pref.getInt("level" + level.toString()) + 1);
                            //print(pref.getInt("level" + level.toString()));
                            Navigator.pushReplacement(context, new MaterialPageRoute(
                                builder: (context) =>
                                    BreakScreen(index: index + 1,
                                      //ccal: ccal,
                                      data: data,
                                      level: level,
                                      paused: paused,
                                    )));
                            return;
                          }},
                        )),
                  ]),
                )],
              ))




    );
  }
}


class Training extends StatefulWidget {
  int lvl,progress;
  final data;
  Training({this.lvl,this.data,this.progress});
  @override
  _TrainingState createState() => _TrainingState(lvl:lvl,data: data,progress: progress);
}
class TrainingAdd extends StatefulWidget {

  final data;
  TrainingAdd({this.data});
  @override
  _TrainingAddState createState() => _TrainingAddState(data: data);
}
class _TrainingAddState extends State<TrainingAdd> with AfterInitMixin<TrainingAdd>{
  final data;

  SharedPreferences prefs;
  //ScrollController _scrollController = new ScrollController();
  List<Color>  mainColors=[Colors.blue, Colors.purple, Colors.red];

  _TrainingAddState({this.data});
  @override
  void didInitState() {
    prefs=Provider.of<Data>(context).prefs;
  }
  @override
  Widget build(BuildContext context) {
    List<Widget> tr=new List();
    int i=0;
    List<int> ex=new List();// todo
    double dur=0;
    for ( var ex in data["exercises"])
    {
      dur+=ex['duration']/1000;
    }
    tr.add(Container(child: Column(crossAxisAlignment: CrossAxisAlignment.start,children:[
      Padding(
        padding: const EdgeInsets.only(left:25.0,bottom: 10),
        child: Text(AppLocalizations.of(context).translate("inst"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 18)),
      ),

      Row(
          children: [Padding(
            padding: const EdgeInsets.only(left:25.0,right: 50),
            child: Column(crossAxisAlignment: CrossAxisAlignment.start,children:[
              Text(data['exercises'].length.toString(),style: TextStyle(fontWeight: FontWeight.bold)),
              Text(AppLocalizations.of(context).translate("exercises")),
            ]),
          ),
            Column(crossAxisAlignment: CrossAxisAlignment.start,children:[
              Text((dur*prefs.getInt("weight")*4.4/3600).floor().toString(),style: TextStyle(fontWeight: FontWeight.bold),),
              Text(AppLocalizations.of(context).translate("cal"))
            ]),
            Padding(
              padding: const EdgeInsets.only(left:50.0),
              child: Column(crossAxisAlignment: CrossAxisAlignment.start,children:[
                Text((((dur/60).floor()>9)?"":'0')+(dur/60).floor().toString()+":"+((((dur.round()%60)>9)?'':"0")+(dur.round()%60).toString()),style: TextStyle(fontWeight: FontWeight.bold)),
                Text(AppLocalizations.of(context).translate("dur"))
              ]),
            )]
      )
    ]),));
    for (var d in data["exercises"]){
      ex.add(i);
      tr.add(Padding(padding: EdgeInsets.all(20),child: Exercise(image: (d["img_key"].toString()),name:d['img_key'].toString() ,count: (d["duration"]/1000).floor(),index:2)));

    }
    tr.add(Container(height: 50,));
    return SafeArea(
      child: Scaffold(
          backgroundColor: Colors.white,
          body: Stack(
            children: [CustomScrollView(
              slivers: <Widget>[

                SliverPersistentHeader(
                    pinned: true,
                    delegate: TrainingHeaderAdd(
                      minExtend: 50,
                      maxExtend: 200,
                      name: data['name'],

                    )
                ),
//
                SliverList(

                  delegate: SliverChildListDelegate(
                    tr,
                  ),
                ),
              ],
            ),
              Positioned(
                bottom: 10,
                left: 10,
                child: SizedBox(
                  width: MediaQuery.of(context).size.width-20,
                  height: 45,
                  child: FlatButton(child: Text(AppLocalizations.of(context).translate("start"),style: TextStyle(fontSize: 18,fontWeight: FontWeight.bold),),color: Color.fromARGB(255,207,78,61),onPressed: (){Navigator.pushReplacement(context,new MaterialPageRoute(builder: (context)=>ExesFull(circle: true,index: 0,level:4,data: data['exercises'],name: data['name'])));},textColor: Colors.white,
                      shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(30.0))),

                ),
              )],
          )
      ),

      //);,
    );

  }
}
class _TrainingState extends State<Training> with AfterInitMixin<Training>{
  int lvl,progress;
  final data;
  SharedPreferences prefs;
  //ScrollController _scrollController = new ScrollController();
  List<Color>  mainColors=[Colors.blue, Colors.purple, Colors.red];

  _TrainingState({this.lvl,this.data,this.progress});
  @override
  void didInitState() {
    prefs=Provider.of<Data>(context).prefs;
  }
  @override
  Widget build(BuildContext context) {
    List<Widget> tr=new List();
    int i=0;
    List<int> ex=new List();// todo
    double dur=0;
    for ( var ex in data["exercises"])
      {
        dur+=ex['duration']/1000;
      }
    tr.add(Container(child: Column(crossAxisAlignment: CrossAxisAlignment.start,children:[
      Padding(
        padding: const EdgeInsets.only(left:25.0,bottom: 10),
        child: Text(AppLocalizations.of(context).translate("inst"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 18)),
      ),

      Row(
        children: [Padding(
          padding: const EdgeInsets.only(left:25.0,right: 50),
          child: Column(crossAxisAlignment: CrossAxisAlignment.start,children:[
            Text(data['exercises'].length.toString(),style: TextStyle(fontWeight: FontWeight.bold)),
            Text(AppLocalizations.of(context).translate("exercises")),
          ]),
        ),
          Column(crossAxisAlignment: CrossAxisAlignment.start,children:[
            Text("~"+(dur*prefs.getInt("weight")*4.4/3600).floor().toString()+' cal',style: TextStyle(fontWeight: FontWeight.bold),),
            Text(AppLocalizations.of(context).translate("cal"))
          ]),
          Padding(
            padding: const EdgeInsets.only(left:50.0),
            child: Column(crossAxisAlignment: CrossAxisAlignment.start,children:[
              Text((((dur/60).floor()>9)?"":'0')+(dur/60).floor().toString()+":"+((((dur.round()%60)>9)?'':"0")+(dur.round()%60).toString()),style: TextStyle(fontWeight: FontWeight.bold)),
              Text(AppLocalizations.of(context).translate("dur"))
            ]),
          )]
      )
    ]),));
    for (var d in data["exercises"]){
      ex.add(i);
      tr.add(Padding(padding: EdgeInsets.all(20),child: Exercise(image: (d["img_key"]),name:d['name_key'] ,count: (d["duration"]/1000).floor(),index:3)));

    }
    tr.add(Container(height: 50,));
    return SafeArea(
      child: Scaffold(
        backgroundColor: Colors.white,
        body: Stack(
          children: [CustomScrollView(
            slivers: <Widget>[

              SliverPersistentHeader(
                pinned: true,
                delegate: TrainingHeader(
                  minExtend: 50,
                  maxExtend: 200,
                  lvl: lvl,
                )
              ),
//
            SliverList(

              delegate: SliverChildListDelegate(
               tr,
              ),
            ),
            ],
          ),
            Positioned(
              bottom: 10,
              left: 10,
              child: SizedBox(
                width: MediaQuery.of(context).size.width-20,
                height: 45,
                child: FlatButton(child: Text(progress==0?AppLocalizations.of(context).translate("start"):AppLocalizations.of(context).translate("continue"),style: TextStyle(fontSize: 18,fontWeight: FontWeight.bold),),color: Color.fromARGB(255,207,78,61),onPressed: (){Navigator.pushReplacement(context,new MaterialPageRoute(builder: (context)=>ExesFull(index: prefs.getInt("level"+(lvl/100).floor().toString())%100,level:(lvl/100).floor(),data: data['exercises'],)));},textColor: Colors.white,
                    shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(30.0))),

              ),
            )],
        )
      ),

        //);,
    );

  }
}
