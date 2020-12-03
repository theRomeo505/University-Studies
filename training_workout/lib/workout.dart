

import 'dart:convert';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:percent_indicator/percent_indicator.dart';
import 'package:provider/provider.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:after_init/after_init.dart';


import 'data.dart';
import 'localization.dart';
import 'training.dart';


class TabsWorkout extends StatefulWidget {
//  const TabsWorkout({Key key}) : super(key: key);
  int index;
  TabsWorkout({this.index=0});
  @override
  _TabsWorkoutState createState() => new _TabsWorkoutState(index: index);
}
class _TabsWorkoutState extends State<TabsWorkout> with SingleTickerProviderStateMixin{
  int index=0;

  TabController _tabController;
  _TabsWorkoutState({this.index=0});
  @override
  void initState() {
    super.initState();
    print(index);
    _tabController = new TabController(vsync: this, length: 3,initialIndex: index);

  }
  @override
  void dispose() {
    _tabController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Stack(

        children: <Widget>[ TabBarView(

            controller: _tabController,
            children: <Widget>[
              WorkoutsElement(index: 1,time:"8-23",image: "assets/train1.jpg",jsonindex:2,/*todo count: from json*/ ),
              WorkoutsElement(index: 2,time:"10-32",image: "assets/train2.jpg",jsonindex:3),
              WorkoutsElement(index: 3,time:"12-40",image: "assets/train3.jpg",jsonindex:4,)]),

          new WorkoutsTabBar(
            ctrl: _tabController,
            barItems: <String>["1 "+AppLocalizations.of(context).translate("lvl"),'2 '+AppLocalizations.of(context).translate("lvl"),'3 '+AppLocalizations.of(context).translate("lvl")],
          ),],
      ),
    );
  }

}

class WorkoutsTabBar extends StatefulWidget{
  final List<String> barItems;
  TabController ctrl;
  WorkoutsTabBar({this.barItems,this.ctrl});
  @override
  createState() => new _WorkoutsTabBarState(barItems: barItems,ctrl: ctrl);
}
class _WorkoutsTabBarState extends State<WorkoutsTabBar>{
  final List<String> barItems;
  TabController ctrl;
  _WorkoutsTabBarState({this.barItems,this.ctrl});

  @override
  Widget build(BuildContext context) {

    return Positioned.fill(

      top: 20,
      child: Align(
        alignment: Alignment.topCenter,
        child: Container(
            margin: EdgeInsets.only(left: 40,right: 40),
            child:
            MyFlatButton(index:ctrl.index,ctrl: ctrl, barItems: barItems,)
        ),
      ),
    );

  }

}

class WorkoutsElement extends StatefulWidget{
  int index;
  String time;
  String image;
  //ouble hardlvl;
  int jsonindex;
  WorkoutsElement({this.index,this.time,this.image,this.jsonindex,});
  @override
  createState()=>new _WorkoutsElementState(index: index,time: time,image: image,jsonindex: jsonindex);
}
class WorkoutsElementAdd extends StatefulWidget {
  int jsonindex;
  WorkoutsElementAdd({this.jsonindex});
  @override
  _WorkoutsElementAddState createState() => _WorkoutsElementAddState(jsonindex: jsonindex);
}

class _WorkoutsElementAddState extends State<WorkoutsElementAdd> {
  int jsonindex;
  _WorkoutsElementAddState({this.jsonindex});
  @override
  Widget build(BuildContext context) {
    List<Widget> days=new List();
    int i=1;
    //print(Provider.of<Data>(context).jsn[0]);

    //print(jjs);

    //print("p");
    //print(jjs);
    for (var el in Provider.of<Data>(context).jsn[jsonindex-1]["data"]){
      //print((prefs.getInt("level"+index.toString())/100).floor()>=i);
      List ex=el["exercises"];
      int dur=0;
      for (var elem in ex)
        dur+=(elem["duration"]/1000).round()+30;
      //print(jsonindex);
      days.add(Container(
        color: Colors.grey.shade300,
        padding: EdgeInsets.only(left:18,top: 18,right: 18),
        child: new DayViewAdd(//index: 1,   /// todo create new dayview
          name: el['name'],
            min: (dur/60).floor(),
            sec: dur%60,
//          sets: (){setState(() {});},

            //lvl: 3,
            //data: Provider.of<Data>(context).jsn[jsonindex-1]["data"]),
      ),));
    }
    return SafeArea(child: Scaffold(body: ListView(
      children: days,
    ),),);
  }
}
class DayViewAdd extends StatelessWidget {
  String name;

  int min;
  int sec;
  DayViewAdd({this.name,this.min,this.sec});
  var data;
  @override
  Widget build(BuildContext context) {
    for (var i in Provider.of<Data>(context).jsn[5]['data'])
      if (i['name']==name)
        data=i;
    //print(index.toString()+isActive.toString());
    //if (lvl==1)
    //print(index.toString()+' '+isActive.toString()+'p');
    //print(AppLocalizations.of(context).translate(name));
    return Container(
      margin: EdgeInsets.only(bottom: 10),
      padding: EdgeInsets.only(left:15,right: 15,top: 10,bottom: 10),
      decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.all(Radius.circular(15))),
      child: Column(crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          Row(children: <Widget>[
            Column(children: <Widget>[
              Text(AppLocalizations.of(context).translate(name),style: TextStyle(fontSize: 19,fontWeight: FontWeight.bold),)
            ],),
            Spacer(),
            Padding(
              padding: const EdgeInsets.only(left: 8.0),
              child: Row(children: <Widget>[

                Icon(Icons.timer,size: 20,),
                Text(min.toString()+":"+((sec/10).floor()==0?"0":"")+sec.toString(),style: TextStyle(fontSize: 20,color: Colors.black),)],),

            ),
            Padding(
              padding: const EdgeInsets.only(left: 8.0),
              child: Row(children: <Widget>[

                Icon(Icons.whatshot,color: Colors.red,size: 20,),
                Text((min*30*4.4*Provider.of<Data>(context).prefs.getInt("weight")/3600).floor().toString(),style: TextStyle(fontSize: 20,color: Colors.black),)],),

            ),

          ],),
          Text(AppLocalizations.of(context).translate(name+'1'),style: TextStyle(fontSize: 14),),
          Padding(
            padding: const EdgeInsets.only(top: 8.0),
            child: SizedBox(
              width: MediaQuery.of(context).size.width-60,
              height: 40,
              child: FlatButton(child: Text(AppLocalizations.of(context).translate("start"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 20),),color: Color.fromARGB(255,207,78,61),onPressed: (){Navigator.push(context,new MaterialPageRoute(builder: (context)=>TrainingAdd(data: data,)));},textColor: Colors.white,
                  shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0))),
            ),
          ),
        ],
      ),
    );
  }
}

class _WorkoutsElementState extends State<WorkoutsElement> with AfterInitMixin<WorkoutsElement>{
  int index;

  String time;
  int jsonindex;
  String image;
  SharedPreferences prefs;
  List<Widget> ic=[];
  List<Color>  mainColors=[Colors.blue, Colors.purple, Colors.red];
  //ScrollController scr= new ScrollController();

  @override
  void initState(){
    super.initState();
    for (int i=0;i<index;i++)
      ic.add(Icon(Icons.star,color: Colors.white,));
    for (int i=3;i>index;i--)
      ic.add(Icon(Icons.star_border,color: Colors.white,));
  }
  @override
  void didInitState(){

    //scr.addListener(() {scr.offset(500)});
    prefs=Provider.of<Data>(context).prefs;
  print(prefs.getKeys());}
  _WorkoutsElementState({this.index,this.time,this.image,this.jsonindex,});

  @override
  Widget build(BuildContext context) {
    //todo reload
    //prefs.setInt("level1", 100);
    //Map<String, dynamic> json = jsonDecode("level"+index.toString()+'.json');
    //fetchJson();
    //print(jsonn['data'][1]);
    //print('reload'+prefs.getInt("level3").toString());
   //return FutureBuilder(future:fetchJson(),builder: (BuildContext context,AsyncSnapshot snapshot){
      //print(snapshot.data["data"][1]["img_src"]);
     // if (!snapshot.hasData){
      //  return Center(child: CircularProgressIndicator());
     // }else{
        List<Widget> days=new List();
        int i=1;
      //print(Provider.of<Data>(context).jsn[0]);

        //print(jjs);

        //print("p");
        //print(jjs);
      for (var el in Provider.of<Data>(context).jsn[jsonindex-1]["data"]){
        //print((prefs.getInt("level"+index.toString())/100).floor()>=i);
        List ex=el["exercises"];
        int dur=0;
        for (var elem in ex)
          dur+=(elem["duration"]/1000).round()+30;

        days.add(new DayView(index: el['level'],

          min: (dur/60).floor(),
          sec: dur%60,
//          sets: (){setState(() {});},

            lvl: index,
            data: Provider.of<Data>(context).jsn[jsonindex-1]["data"]),);
        i++;
      }
      //print(days);
      return Column(
        children: <Widget>[
          Container(
            child: Stack(

              children: <Widget>[
                Image.asset(image,alignment: Alignment.topCenter,),
                Padding(
                  padding: const EdgeInsets.only(top: 80,left: 25,bottom: 10),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: <Widget>[
                      Row(
                        children: ic,
                      ),
                      Stack(

                        alignment: Alignment.bottomCenter,
                        children: <Widget>[
                          Container(
                            color: mainColors[index-1],
                            height: 15,
                            width: 140,
                          ),
                          Text(AppLocalizations.of(context).translate('lvl').toUpperCase()+' '+index.toString(),style: TextStyle(fontSize: 30,color: Colors.white,fontWeight: FontWeight.bold),)
    ],
                      ),
                      Padding(
                        padding: const EdgeInsets.only(top: 10,bottom: 5),
                        child: Row(
                          children: <Widget>[
                            Icon(Icons.timer,color: Colors.white,size: 20,),
                            Text("  "+time+' '+AppLocalizations.of(context).translate('minperd'), style: TextStyle(color: Colors.white,fontSize: 16,fontWeight: FontWeight.w600),),
                          ],
                        ),   //todo

                      ), // todo percent
                      Row(
                        children: <Widget>[
                          CircularPercentIndicator(
                            lineWidth: 3,
                            center: Text(''),
                            radius: 20,
                            progressColor: Colors.white,
                            percent: ((prefs.getInt("level"+index.toString())/100).floor()-1)/Provider.of<Data>(context).jsn[index-1]["data"].length

                          ),

                          Text("  "+(((prefs.getInt("level"+index.toString())/100).floor()-1)/Provider.of<Data>(context).jsn[index-1]["data"].length*100).round().toString()+"% "+AppLocalizations.of(context).translate("completed"), style: TextStyle(color: Colors.white,fontSize: 16,fontWeight: FontWeight.w600)),
                        ],
                      ),

                    ],
                  ),
                ),
                Positioned(
                  bottom: -1,
                  child: Container(height: 10,width: MediaQuery.of(context).size.width,decoration: BoxDecoration(color: Color.fromARGB(255, 230, 230, 230),borderRadius: BorderRadius.only(topLeft: Radius.circular(20),topRight: Radius.circular(20))),),
                )
              ],
            ),
          ),
//          SliverFillRemaining(
//            child: Container(color: Colors.red,),
//          )
//
          Expanded(
            flex: 1,
            child: Container(

                    padding: EdgeInsets.only(left: 15,top: 5,right: 15,),
                    //height: 300,

                    width: MediaQuery.of(context).size.width,
                    decoration: BoxDecoration(color: Color.fromARGB(255, 230, 230, 230)),
                    child: ListView(
                          controller: new ScrollController(initialScrollOffset: 91.0*((prefs.getInt("level"+index.toString())/100).floor()-1)),
                          children: days,
                      ),


                  ),
          ),
        ],
      );
  }
}


class MyFlatButton extends StatefulWidget{
  int index;
  final List<String> barItems;
  TabController ctrl;
  MyFlatButton({this.index,this.ctrl,this.barItems});

  @override
  createState() => new MyFlatbuttonState(index: index,ctrl: ctrl, barItems: barItems,);


}
class MyFlatbuttonState extends State<MyFlatButton>{
  int index;
  final List<String> barItems;
  TabController ctrl;
  List<Color>  mainColors=[Colors.blue, Colors.purple, Colors.red];
  @override
  void initState() {
    super.initState();
    ctrl.animation.addListener((){
      //if (status==AnimationStatus.forward) {
      if (index!=((ctrl.animation.value.ceil()-ctrl.animation.value)<0.5?ctrl.animation.value.ceil():ctrl.animation.value.floor()))
        setState(() {
          index = (ctrl.animation.value.ceil()-ctrl.animation.value)<0.5?ctrl.animation.value.ceil():ctrl.animation.value.floor();
        });

      //}
    });
  }
  MyFlatbuttonState({this.index,this.ctrl,this.barItems});
  @override
  Widget build(BuildContext context) {
    List<Widget> buttons=List();
    for (var i=0;i<barItems.length;i++){
      buttons.add(SizedBox(
        height: 32,
        child: FlatButton(shape:RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(15.0),
        ),textColor: Colors.white,color: (i==index)?mainColors[i]:Colors.transparent,child: Text(barItems[i],style: TextStyle(fontSize: 14),),onPressed: (){setState(() {
          index=i;
        });ctrl.animateTo(i);},),
      ));
    }
    return Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: buttons,);

  }

}

class DayView extends StatefulWidget{
  int index, min,sec,lvl;
  final data;
  DayView({this.index,this.min,this.sec,this.lvl,this.data});

  @override
  createState()=> new _DayViewState(index: index,min: min,sec:sec,lvl: lvl,data: data);
}
class _DayViewState extends State<DayView> with AfterInitMixin<DayView>{

  final data;

  int progress,index, min,sec,lvl;
  bool isActive;
  int length;
  _DayViewState({this.index,this.min,this.sec,this.lvl,this.data});
  SharedPreferences prefs;

  @override
  void didInitState() {
    prefs=Provider.of<Data>(context).prefs;
    isActive=(prefs.getInt("level"+lvl.toString())/100).floor()>=index;
    List l=data[index-1]["exercises"];
    length=l.length;
    progress=(prefs.getInt("level"+lvl.toString())/100).floor()==index?(prefs.getInt("level"+lvl.toString())%100*100/length).ceil():prefs.getInt("level"+lvl.toString())/100>index?100:0;
  }
@override
void didUpdateWidget(DayView oldWidget) {
  setState(() {
    isActive=(Provider.of<Data>(context).prefs.getInt("level"+lvl.toString())/100).floor()>=index;
    progress=(prefs.getInt("level"+lvl.toString())/100).floor()==index?(prefs.getInt("level"+lvl.toString())%100*100/length).ceil():prefs.getInt("level"+lvl.toString())/100>index?100:0;
  });
  super.didUpdateWidget(oldWidget);
  }
  @override
  Widget build(BuildContext context) {
    List<double> wid=[1.4,1,0.8];
    //print(index.toString()+isActive.toString());
    //if (lvl==1)
    //print(index.toString()+' '+isActive.toString()+'p');
    var a=(((min*60+sec)*progress)*wid[lvl-1]/(900.0));
    return Container(
      margin: EdgeInsets.only(bottom: 10),
      padding: EdgeInsets.only(left:15,right: 15,top: 10,bottom: 10),
      decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.all(Radius.circular(15))),
      child: Column(
        children: <Widget>[
          Row(children: <Widget>[
            Column(children: <Widget>[
              Text(AppLocalizations.of(context).translate("day").toUpperCase(),style: TextStyle(fontWeight: FontWeight.bold,color: Colors.grey.shade600),),
              Text(index.toString(),style: TextStyle(fontSize: 30,fontWeight: FontWeight.bold),)
            ],),
            Padding(
              padding: const EdgeInsets.only(left: 18.0),
              child: Column(crossAxisAlignment:CrossAxisAlignment.start,children: <Widget>[Row(children: <Widget>[

                Icon(Icons.timer,size: 16,),
                Text(min.toString()+":"+((sec/10).floor()==0?"0":"")+sec.toString(),style: TextStyle(fontSize: 18,color: isActive?Colors.black:Colors.grey),)],),
              Stack(
                children: [Container(
                  margin: EdgeInsets.only(top: 3),
                  decoration: BoxDecoration(color: Color.fromARGB(255, 230, 230, 230),borderRadius: BorderRadius.all(Radius.circular(15))),
                  height: 5,
                  width: (min*60+sec)*wid[lvl-1]/(9),//todoo

                ),
                  Container(margin: EdgeInsets.only(top: 3),width: a,height: 5,decoration: BoxDecoration(color: Color.fromARGB(255,207,78,61),borderRadius: BorderRadius.all(Radius.circular(15))),),
              ])],),
            ),
            Spacer(),
            isActive?CircularPercentIndicator(radius: 50.0,
              lineWidth: 4.0,
              percent: progress/100,
              backgroundColor: Color.fromARGB(255, 230, 230, 230),
              center: new Text("  "+progress.toString()+"%"),
              progressColor: Color.fromARGB(255,207,78,61),):Container(width: 60,height: 60,child: Icon(Icons.no_encryption,color: Color.fromARGB(255, 230, 230, 230),)
              ,)
          ],),
          isActive&&progress!=100?Padding(
            padding: const EdgeInsets.only(top: 8.0),
            child: SizedBox(
              width: MediaQuery.of(context).size.width-60,
              height: 40,
              child: FlatButton(child: Text(progress==0?AppLocalizations.of(context).translate("start"):AppLocalizations.of(context).translate("continue"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 20),),color: Color.fromARGB(255,207,78,61),onPressed: (){Navigator.push(context,new MaterialPageRoute(builder: (context)=>Training(lvl:(lvl*100)+index,progress: progress,data: data[index-1])));},textColor: Colors.white,
                     shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0))),
            ),
          ):Text('',style: TextStyle(fontSize: 5),),
        ],
      ),
    );
  }

}
class Workouts extends StatelessWidget {
  int index;
  Workouts({this.index=0});
  @override
  Widget build(BuildContext context) {
    //print(index);
    return SafeArea(
      child: new Scaffold(
        body: TabsWorkout(index: index),
      ),
    );

  }
}