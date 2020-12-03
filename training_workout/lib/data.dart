
import 'dart:convert';
import 'dart:io';
import 'dart:async' as async;
import 'package:android_alarm_manager/android_alarm_manager.dart';
import 'package:firebase_admob/firebase_admob.dart';
import 'package:flutter/services.dart';
//import 'package:flutter_local_notifications/flutter_local_notifications.dart';
import 'package:package_info/package_info.dart';
import 'package:path_provider/path_provider.dart';
import 'dart:async';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:soundpool/soundpool.dart';
import 'localization.dart';
import 'main.dart';

class Data {
  AppLanguage appLanguage=new AppLanguage();
  //final d=fetchJson();
  SharedPreferences prefs;
  String version;
  String data ;
  //InterstitialAd myInterstitial;

  List<String> trains=[''];
  Soundpool pool = Soundpool(streamType: StreamType.notification);
  List<String> sound=['go','finish','number_1',"number_2","number_3",'ready','rest'];
  //FlutterLocalNotificationsPlugin plugin;
  var jsn;
//  Data(){
//    update();
//
//  }
//  setPlugin(FlutterLocalNotificationsPlugin plugin){
//    this.plugin=plugin;
//  }
  int find(String s){
    for (int i=0;i<sound.length;i++){
      if (sound[i]==s)
        return i+1;
    }
    return 0;
  }
  jsonn() async{
    return await  rootBundle.loadString("assets/level1.json");
  }
  update() async{
    await appLanguage.fetchLocale();

    prefs=await SharedPreferences.getInstance();
    if (!prefs.containsKey("level1")||!prefs.containsKey("level2")||!prefs.containsKey("level3"))
    {
      prefs.setInt("level1", 100);
      prefs.setInt("level2", 100);
      prefs.setInt("level3", 100);
      prefs.setInt("level4", 100);
      prefs.setInt("enter", 0);
      prefs.setInt("notification", 1800);
      prefs.setBool("first", true);
      DateTime d= new DateTime.now(),dd;


      int h=prefs.getInt("notification");

      not1(false);

      dd=new DateTime(d.year,d.month,d.day,(h/100).floor(),h%100);
      if ((h/100).floor()<d.hour || ((h/100).floor()==d.hour && h%100<=d.minute))
      {
        //print('add');
        dd=dd.add(Duration(days:1));

      }
          ()async=> await AndroidAlarmManager.oneShotAt(dd, alarmId, not);
      //daily(Provider.of<Data>(context).plugin,((Provider.of<Data>(context).prefs.getInt("notification")??1800)/100).floor(),(Provider.of<Data>(context).prefs.getInt("notification")??0)%100);
    }else
      not1(true);
    if (!prefs.containsKey("weight")){
      prefs.setInt("weight", 50);
    }
    await readcontent();
    data = await rootBundle.loadString("assets/level11.json");
    final json1=  await json.decode(data);
    //print(1);
    data = await rootBundle.loadString("assets/level12.json");
    final json2=  await json.decode(data);
    var jss=await json.decode(data);
    //print(jss);
    for ( var el in jss['data']){
      for (var ell in el["exercises"])
        ell['duration']=ell['duration']*1.5;
    }
    final jss1=await json.decode(data);
    for ( var el in jss1['data']){
      for (var ell in el["exercises"])
        ell['duration']=ell['duration']*2;
    }
    //print(2);
    data = await rootBundle.loadString("assets/level13.json");
    final json3=  await json.decode(data);
    data = await rootBundle.loadString("assets/new.json");
    final newjs=json.decode(data);
    //print(3);
    jsn=[json1,json2,jss,jss1,json3,newjs];
    //print(newjs);
  PackageInfo packageInfo= await PackageInfo.fromPlatform();
  version=packageInfo.version;

    for (var i in sound){
      int soundId = await rootBundle.load("assets/raw-"+appLanguage.applocale.languageCode+"/"+i+".mp3").then((ByteData soundData) {
        return pool.load(soundData);
      });
//      FirebaseAdMob.instance.initialize(appId: "ca-app-pub-8214508586760060~3710668896");
//
//      MobileAdTargetingInfo targetingInfo = MobileAdTargetingInfo(
//        keywords: <String>['flutterio', 'beautiful apps'],
//        contentUrl: 'https://flutter.io',
//        //birthday: DateTime.now(),
//        //childDirected: false,
//        //designedForFamilies: false,
//        gender: MobileAdGender.female, // or MobileAdGender.female, MobileAdGender.unknown
//        testDevices: <String>[], // Android emulators are considered test devices
//      );
//
//      myInterstitial = InterstitialAd(
//        // Replace the testAdUnitId with an ad unit id from the AdMob dash.
//        // https://developers.google.com/admob/android/test-ads
//        // https://developers.google.com/admob/ios/test-ads
//        //adUnitId: "ca-app-pub-8214508586760060/6009814582",
//        adUnitId: BannerAd.testAdUnitId,
//        targetingInfo: targetingInfo,
//        listener: (MobileAdEvent event) {
//          print("InterstitialAd event is $event");
//        },
//      );
//      await myInterstitial.load();
//      myInterstitial
//        ..load()
//        ..show(
//          anchorType: AnchorType.bottom,
//          anchorOffset: 0.0,
//          horizontalCenterOffset: 0.0,
//        );
      //myInterstitial.load();
      //await myInterstitial.isLoaded();
      //print("loadd");
      //print(soundId);
    }
    return prefs;
  }
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
  void readcontent() async {
    try {
      final file = await _localFile;
      //print(await file.exists());
      // Read the file
      if (await file.exists()) {
        List<String> contents = await file.readAsLines();
        trains = contents;

      }
      else
        trains=[];
    } catch (e) {
      // If there is an error reading, return a default String
      print('Error');
    }
  }

}