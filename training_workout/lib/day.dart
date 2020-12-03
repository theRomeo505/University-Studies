
import 'dart:io';

import 'package:after_init/after_init.dart';
import 'package:dotted_border/dotted_border.dart';
import 'package:intl/intl.dart';
import 'package:training_workout/aboutme.dart';
import 'package:training_workout/localization.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:path_provider/path_provider.dart';
import 'package:percent_indicator/circular_percent_indicator.dart';
import 'package:provider/provider.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'dart:math' as math;
import 'data.dart';
import 'package:md2_tab_indicator/md2_tab_indicator.dart';

class Days extends StatefulWidget {
  List<String> data;
  Days({this.data});
  @override
  _DaysState createState() => _DaysState(data: data);
}



class _DaysState extends State<Days> {
  List<Widget> d ;

  List<String> data;
  _DaysState({this.data});
  @override
  Widget build(BuildContext context) {
    List<String> dayss=["mon","tue","wed","th","fr",'sat','sun'];
    List<int> dayswithtrainswithweek=new List();
    d=new List();
    //print(int.tryParse("oio"));
    for (int i=data.length-1;i>=0;i--){
      List info=data[i].split(" ").toList().map((e) =>  int.tryParse(e)!=null?int.parse(e):e).toList();
      //print(info);
      DateTime dateTime=new DateTime(info[2],info[1],info[0]);
      if (DateTime.now().difference(dateTime).inDays>DateTime.now().weekday)
        break;

        dayswithtrainswithweek.add(info[0]);
    }

    for (var i=0;i<7;i++) {
      bool flag=false;
      for (int j in dayswithtrainswithweek)
        if (j==(DateTime.now().subtract(Duration(days: DateTime.now().weekday-1))).add(Duration(days: i)).day)
          {flag=true; break;}
      var color = (DateTime.now().subtract(Duration(days: DateTime.now().weekday-1))).add(Duration(days: i)).day==DateTime.now().day?flag?Color.fromARGB(255, 207, 78, 61):Colors.black:flag?Color.fromARGB(255, 207, 78, 61):Color.fromARGB(255, 247, 247, 247);
      var txtclr=(DateTime.now().subtract(Duration(days: DateTime.now().weekday-1))).add(Duration(days: i)).day==DateTime.now().day||flag?Colors.white:Colors.grey.shade400;
      d.add(Column(children: <Widget>[Text(AppLocalizations.of(context).translate(dayss[i]).substring(0,1),style: TextStyle(color: Colors.grey),),
        Container(
            margin: EdgeInsets.only(top:25),
            width: 35,
            height: 35,
            decoration: BoxDecoration(color: color,
                borderRadius: BorderRadius.all(Radius.circular(30))),
            child: Center(
                child: Text((DateTime.now().subtract(Duration(days: DateTime
                    .now()
                    .weekday - 1)))
                    .add(Duration(days: i))
                    .day
                    .toString(), style: TextStyle(color: txtclr,fontSize: 14,fontWeight: FontWeight.bold),)))
      ]));

    }
    return  Container(margin: EdgeInsets.only(left:10,right: 10),
      child: Material(
        borderRadius: BorderRadius.all(Radius.circular(15)),
        color: Colors.white,
        child: InkWell(
          borderRadius: BorderRadius.all(Radius.circular(15)),
          child:Padding(
            padding: const EdgeInsets.all(20.0),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: d,
            ),
          ),
          onTap: (){Navigator.push(context, MaterialPageRoute(builder: (context)=>Time(data: data,init: 1,)));},
        ),
      ),
    );
  }
}

class TrainingTime extends StatefulWidget {
  List<String> data;
  TrainingTime({this.data});
  @override
  _TrainingTimeState createState() => _TrainingTimeState(data:data);
}

class _TrainingTimeState extends State<TrainingTime> {
  List<String> data;
  _TrainingTimeState({this.data});

  @override
  Widget build(BuildContext context) {
    List<String> days=["mon","tue","wed","th","fr",'sat','sun'];

    days=days.map((e)=>AppLocalizations.of(context).translate(e)).toList();
    //double avg=0,today=0;int j=0,jj=0;
    List<int> av=[0,0,0,0,0,0,0];

    for (int i=data.length-1;i>=0;i--){
      List info=data[i].split(" ").toList().map((e) =>  int.tryParse(e)!=null?int.parse(e):e).toList();
      DateTime dateTime=new DateTime(info[2],info[1],info[0]);

      if (DateTime.now().difference(dateTime).inDays>DateTime.now().weekday)
        break;

      av[dateTime.weekday-1]+=info[5];
    }
    double avg=0;
    List<Widget> sticks=new List();

    for (int i=0;i<7;i++){
      avg+=(av[i]);
      sticks.add(Column(children: <Widget>[
        Container(margin: EdgeInsets.only(bottom: 8),width: 10,height: 10.0+40*av[i]/(av.reduce(math.max)==0.0?1.0:av.reduce(math.max)),decoration: BoxDecoration(color: DateTime.now().weekday==i+1||av[i==6?0:(i)]!=0?Color.fromARGB(255, 207, 78, 61):Color.fromARGB(100, 207, 78, 61),borderRadius: BorderRadius.all(Radius.circular(20))),),
        Text(days[i].substring(0,1))
      ],));

    }
    avg=(avg/7);
    Path customPath = Path()
      ..moveTo(0, 35)
      ..lineTo(MediaQuery.of(context).size.width-60, 35);

      return  Container(margin: EdgeInsets.only(left:10,right: 10,top: 10),
      child: Material(
        borderRadius: BorderRadius.all(Radius.circular(15)),
        color: Colors.white,
        child: InkWell(
          borderRadius: BorderRadius.all(Radius.circular(15)),
          child:Padding(
            padding: const EdgeInsets.all(20.0),
            child: Column(children: <Widget>[
              Row(children: <Widget>[
                Icon(Icons.timer,color: Color.fromARGB(255, 207, 78, 61),size: 20,),
                Text(" "+AppLocalizations.of(context).translate("tab2"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 18),),
              ],),
              Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: <Widget>[
                Row(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: <Widget>[
                    Text((av[DateTime.now().weekday-1]).toString(),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 22)),
                    Padding(
                      padding: const EdgeInsets.only(left:3.0,top: 7),
                      child: Text(AppLocalizations.of(context).translate("min"),style: TextStyle(fontWeight: FontWeight.bold),),
                    )
                  ],
                ),
                Column(crossAxisAlignment: CrossAxisAlignment.end,children: <Widget>[
                  Text(AppLocalizations.of(context).translate("avg"),style: TextStyle(color: Colors.grey),),
                  Padding(
                    padding: const EdgeInsets.only(top:5.0),
                    child: Text(avg.round().toString()+" "+AppLocalizations.of(context).translate("min"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 14)),
                  )
                ],)
              ],),
              Padding(
                padding: EdgeInsets.only(top:(avg.round()==0)?60.0:5),
                child: Stack(
                  children: [
                   avg!=0.0?DottedBorder(dashPattern: [5],
                     strokeWidth: 1,
                     customPath: (size)=>customPath,
                     color: Colors.grey,
                     child: Container(),):Text("") ,
                  Row(
                    mainAxisAlignment: MainAxisAlignment.spaceAround,
                      crossAxisAlignment: CrossAxisAlignment.end,
                      children: sticks,
                  )],
                ),
              ),
            ],)
          ),
          onTap: (){Navigator.push(context, new MaterialPageRoute(builder: (context)=>Time(init: 0,data:data)));},
        ),
      ),
    );  }
}
class Time extends StatefulWidget{
  int init;
  List<String> data;
  Time({this.init,this.data});
  @override
  createState()=> TimeState(init: init,data: data);
}
class TimeState extends State<Time> with TickerProviderStateMixin{
  int init;
  List<String> data;
  //int index;

  TimeState({this.init,this.data});

  @override
  Widget build(BuildContext context) {
    List<Widget> histr=new List();
    List<Widget> colum=new List();
    List<String> days=["mon","tue","wed","th","fr",'sat','sun'];
    List<String> month=["jan","feb",'mar','apr','may','jun','jul',"aug","sep",'oct','nov','dec'];
    days=days.map((e)=>AppLocalizations.of(context).translate(e)).toList();
    month=month.map((e)=>AppLocalizations.of(context).translate(e)).toList();
    List<bool> flag=new List(31);
    flag=flag.map((e) => false).toList();
    List<List<List>> weeks=[[[DateTime.now().subtract(Duration(days: DateTime.now().weekday-1)).day*10000+DateTime.now().month*100+DateTime.now().year%100]]];
    DateTime lasttr=DateTime.now();
    for (int i=data.length-1;i>=0;i--){
      List info=data[i].split(" ").toList().map((e) =>  int.tryParse(e)!=null?int.parse(e):e).toList();
      DateTime dateTime=new DateTime(info[2],info[1],info[0]);
      if (lasttr.difference(dateTime).inDays>lasttr.weekday){
        weeks.add([[0]]);
        weeks[weeks.length-1][0][0]=dateTime.subtract(Duration(days: dateTime.weekday-1)).day*10000+dateTime.month*100+dateTime.year%100;
        //weeks.add(new List<List<int>>());
      }
      weeks[weeks.length-1>=0?weeks.length-1:0].add(info);
      lasttr=dateTime;

    }
    //print(weeks);
    for (int i=data.length-1;i>=0;i--){
      List info=data[i].split(" ").toList().map((e) =>  int.tryParse(e)!=null?int.parse(e):e).toList();
      DateTime dateTime=new DateTime(info[2],info[1],info[0]);

      if (DateTime.now().month>dateTime.month)
        break;
      flag[dateTime.day-1]=true;
    }

    colum.add(
        Padding(
          padding: const EdgeInsets.only(bottom:13.0,top:5),
          child: Text(month[DateTime.now().month-1]+' '+DateTime.now().year.toString()),
        ));
    colum.add(Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly,children: days.map((e) => Container(height:40,width:40,child: Align(alignment: Alignment.center,child: Text(e)))).toList()));

    //DateTime monday=DateTime(DateTime.now().year,DateTime.now().month,1);
    DateTime monday=DateTime(DateTime.now().year,DateTime.now().month,1);
    monday=monday.subtract(Duration(days: monday.weekday-1));
    while (monday.month<=DateTime.now().month){
      //print(monday);
      List<Widget> temp=new List();

      for (int i=0;i<7;i++)
        temp.add(monday.add(Duration(days: i)).month==DateTime.now().month?Container(margin: EdgeInsets.only(bottom: 10,top: 10),width: 40,height: 40,decoration: BoxDecoration(color: (monday.add(Duration(days: i)).day!=DateTime.now().day)?(flag[monday.add(Duration(days: i)).day-1]?Color.fromARGB(255, 207, 78, 61):Color.fromARGB(255, 245, 245, 245)):(flag[monday.add(Duration(days: i)).day-1]?Color.fromARGB(255, 207, 78, 61):Color.fromARGB(255, 50, 50, 50)),borderRadius: BorderRadius.all(Radius.circular(20))),
            child: Align(alignment: Alignment.center,child: Text(monday.add(Duration(days: i)).day.toString(),style: TextStyle(color: flag[monday.add(Duration(days: i)).day-1]||monday.add(Duration(days: i)).day==DateTime.now().day?Colors.white:Colors.grey.shade700),))):Container(width: 40,height: 40,));
      colum.add(Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly,children: temp,));
      monday=monday.add(Duration(days: 7));
    }
    histr.add(Container(
      margin: EdgeInsets.all(10),
      decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.all(Radius.circular(20))),
      padding: EdgeInsets.all(10),
      child: Column(children: colum),
    ));

    for (var week in weeks){
      List<Widget> temp=new List();
      if (weeks.length!=1 && week.length!=1){
      temp.add(Container(decoration: BoxDecoration(color: Color.fromARGB(255, 240, 240, 240),borderRadius: BorderRadius.only(topRight: Radius.circular(20),topLeft: Radius.circular(20)),),
        padding: EdgeInsets.all(10),
        child: Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[
          Column(crossAxisAlignment: CrossAxisAlignment.start,children: <Widget>[
            Text((week[0][0]/10000).floor().toString()+' '+(month[DateTime(2000+week[0][0]%100,(week[0][0]/100).floor()%100-1,(week[0][0]/10000).floor()).month])+'-'+(week[0][0]/10000+6).floor().toString()+' '+(month[DateTime(2000+week[0][0]%100,(week[0][0]/100).floor()%100-1,(week[0][0]/10000).floor()).add(Duration(days: 6)).month]),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 16),),
            Text("20"+(week[0][0]%100).toString()),
          ],),
          Column(crossAxisAlignment:CrossAxisAlignment.end,children: <Widget>[
            Text((week.length-1).toString(),style: TextStyle(fontSize: 22,fontWeight: FontWeight.bold),),
            Text(AppLocalizations.of(context).translate("tab2"))
          ],)
        ],),
      ));}
      //List<Widget> tempo=new List();

      for (int i=1;i<week.length;i++){
        //print(week[i]);
        temp.add(Container(
          padding: EdgeInsets.all(10),
          child: Row(
              children: <Widget>[
            Image.asset("assets/train"+(((week[i][3]/100).floor())==4?3:((week[i][3]/100).floor())).toString()+'.jpg',width: 100,),
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: Column(crossAxisAlignment: CrossAxisAlignment.start,children: <Widget>[
               Text(((week[i][3]/100).floor()!=4)?(AppLocalizations.of(context).translate("tab1")+" "+(week[i][3]%100).toString()+'. '+AppLocalizations.of(context).translate("lvl")+' '+(week[i][3]/100).floor().toString()):AppLocalizations.of(context).translate(week[i][6]),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 18)),
                  Container(width: MediaQuery.of(context).size.width-156,child: Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[
                  Column(crossAxisAlignment: CrossAxisAlignment.start,children: <Widget>[
                    Text(week[i][0].toString()+' '+month[week[i][1]-1]),
                  Text(days[DateTime(2000+week[0][0]%100,(week[0][0]/10000).floor()%100,(week[0][0]%100/10000).floor()).weekday-1])]),
                  Column(crossAxisAlignment: CrossAxisAlignment.start,children: <Widget>[
                    Text(week[i][5].toString()+" "+AppLocalizations.of(context).translate("min")),
                    Text(AppLocalizations.of(context).translate("dur"))
                  ],),
                  Column(crossAxisAlignment: CrossAxisAlignment.start,
                    children: [Text(week[i][4].toString()),
                    Text(AppLocalizations.of(context).translate("cal"))],
                  )
                ],))
              ],),
            )
          ],),
        ));
      }

      histr.add(Container(
        margin: EdgeInsets.only(left:10,right: 10,top:10 ),
        decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.all(Radius.circular(20))),
        //padding: EdgeInsets.all(10),
        child: Column(children: temp),
      ));
    }
    TabController t=TabController(length: 2,vsync: this,initialIndex: init);

    t.animation.addListener(() {        //print(t.animation.value);
     if (t.index==0 && t.animation.value>0.5 && init!=1) setState(() {
     // print(t.animation.value);
      init=1;
    }); if (t.index==1 && t.animation.value<0.5 && init!=0)
      setState(() {

        init=0;
      });
    });
    t.addListener(() {if (t.indexIsChanging)setState(() {
      init=t.index;
    });});
    return Scaffold(

        backgroundColor: Color.fromARGB(255, 230, 230, 230),
    appBar: AppBar(title: Text(AppLocalizations.of(context).translate("tab2").toUpperCase(),style: TextStyle(color: Colors.black,fontWeight: FontWeight.bold),),iconTheme: IconThemeData(color: Colors.black),),
    body: //DefaultTabController(
      //initialIndex: init,
      //length: 2,

      //child:
     Scaffold(
        backgroundColor: Color.fromARGB(255, 230, 230, 230),
        appBar: TabBar(
          //:TextStyle(color:Colors.blue),
          controller: t,
          //indicatorColor: Color.fromARGB(a, r, g, b),
          //indicatorPadding: EdgeInsets.only(left: MediaQuery.of(context).size.width/5,right: MediaQuery.of(context).size.width/5,bottom: 12),
          //indicatorWeight: 5,
          indicator: UnderlineTabIndicator(
              borderSide: BorderSide(color: Color.fromARGB(255, 207, 78, 61),width: 3,style: BorderStyle.solid),
            insets: EdgeInsets.only(left: MediaQuery.of(context).size.width/4.5,right: MediaQuery.of(context).size.width/4.5,bottom: 2,top: 0),
          ),

          //indicatorPadding: EdgeInsets.all(20),
          tabs: <Widget>[

          Tab(child: Text(AppLocalizations.of(context).translate("week"),style: TextStyle(color: init==0?Colors.black:Colors.grey),)),
          Tab(child:Text(AppLocalizations.of(context).translate("his"),style: TextStyle(color: init==1?Colors.black:Colors.grey),))
        ],),
        body: TabBarView(
          controller: t,
          children: <Widget>[
            History(data: data,isCal: false,),
            ListView(children: histr,)
          ],
        ),
      ),

   // )
    );
  }
}

class TrainingCall extends StatefulWidget {
  List<String> data;
  TrainingCall({this.data});
  @override
  _TrainingCallState createState() => _TrainingCallState(data:data);
}

class _TrainingCallState extends State<TrainingCall> {
  List<String> data;
  _TrainingCallState({this.data});

  @override
  Widget build(BuildContext context) {
    List<String> days=["mon","tue","wed","th","fr",'sat','sun'];

    days=days.map((e)=>AppLocalizations.of(context).translate(e)).toList();
    //double avg=0,today=0;int j=0,jj=0;
    List<int> av=[0,0,0,0,0,0,0];
    print(data);
    for (int i=data.length-1;i>=0;i--){
      List info=data[i].split(" ").toList().map((e) =>  int.tryParse(e)!=null?int.parse(e):e).toList();
      DateTime dateTime=new DateTime(info[2],info[1],info[0]);

      if (DateTime.now().difference(dateTime).inDays>DateTime.now().weekday)
        break;

      av[dateTime.weekday-1]+=info[4];
    }
    double avg=0;
    List<Widget> sticks=new List();

    for (int i=0;i<7;i++){
      avg+=(av[i]);

      sticks.add(Column(children: <Widget>[
        Container(margin: EdgeInsets.only(bottom: 8),width: 10,height: 10+40*av[i]/(av.reduce(math.max)==0?1.0:av.reduce(math.max)),decoration: BoxDecoration(color: DateTime.now().weekday==i+1||av[i==6?0:(i)]!=0?Color.fromARGB(255, 207, 78, 61):Color.fromARGB(100, 207, 78, 61),borderRadius: BorderRadius.all(Radius.circular(20))),),
        Text(days[i].substring(0,1))
      ],));

    }
    avg=(avg/7);
    Path customPath = Path()
      ..moveTo(0, 35)
      ..lineTo(MediaQuery.of(context).size.width-60, 35);

    return  Container(margin: EdgeInsets.only(left:10,right: 10,top: 10),
      child: Material(
        borderRadius: BorderRadius.all(Radius.circular(15)),
        color: Colors.white,
        child: InkWell(
          borderRadius: BorderRadius.all(Radius.circular(15)),
          child:Padding(
              padding: const EdgeInsets.all(20.0),
              child: Column(children: <Widget>[
                Row(children: <Widget>[
                  Icon(Icons.whatshot,color: Color.fromARGB(255, 207, 78, 61),size: 20,),
                  Text(" "+AppLocalizations.of(context).translate("cal"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 18),),
                ],),
                Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: <Widget>[
                    Row(
                      crossAxisAlignment: CrossAxisAlignment.start,

                      children: <Widget>[
                        Text((av[DateTime.now().weekday-1]).toString(),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 22)),
                        Padding(
                          padding: const EdgeInsets.only(left:3.0,top: 7),
                          child: Text(AppLocalizations.of(context).translate("cal").toLowerCase(),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 15),),
                        )
                      ],
                    ),
                    Column(crossAxisAlignment:CrossAxisAlignment.end,
                      children: <Widget>[
                      Text(AppLocalizations.of(context).translate("avg"),style: TextStyle(color: Colors.grey),),
                      Padding(
                        padding: const EdgeInsets.only(top:5.0),
                        child: Text(avg.round().toString()+" "+AppLocalizations.of(context).translate("cal").toLowerCase(),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 14)),
                      )
                    ],)
                  ],),
                Padding(
                  padding:  EdgeInsets.only(top:(avg==0.0)?60.0:5),
                  child: Stack(
                    children: [
                      avg!=0.0?DottedBorder(dashPattern: [5],
                        strokeWidth: 1,
                        customPath: (size)=>customPath,
                        color: Colors.grey,
                        child: Container(),):Text("") ,
                      Row(
                        mainAxisAlignment: MainAxisAlignment.spaceAround,
                        crossAxisAlignment: CrossAxisAlignment.end,
                        children: sticks,
                      )],
                  ),
                ),
              ],)
          ),
          onTap: (){
            Navigator.push(context, new MaterialPageRoute(builder:  (context)=>Callories(data: data,isCal: true,)));
          },
        ),
      ),
    );  }
}
class Callories extends StatelessWidget {
  bool isCal;
  List<String> data;
  Callories({this.isCal,this.data});
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        backgroundColor: Color.fromARGB(255, 230, 230, 230),
    appBar: AppBar(title: Text(AppLocalizations.of(context).translate("cal"),style: TextStyle(color: Colors.black),),iconTheme: IconThemeData(color: Colors.black),),
    body: History(data: data,isCal: isCal,)
    );
  }
}

class History extends StatelessWidget {
  List<String> data;
  bool isCal;
  History({this.data,this.isCal});
  @override
  Widget build(BuildContext context) {
    List<String> days=["mon","tue","wed","th","fr",'sat','sun'];
    List<String> month=["jan","feb",'mar','apr','may','jun','jul',"aug","sep",'oct','nov','dec'];
    days=days.map((e)=>AppLocalizations.of(context).translate(e)).toList();
    month=month.map((e)=>AppLocalizations.of(context).translate(e)).toList();
    List<List<int>> weeks=[[DateTime.now().subtract(Duration(days: DateTime.now().weekday-1)).day*10000+DateTime.now().month*100+DateTime.now().year%100,0,0,0,0,0,0,0]];
    DateTime lasttr=DateTime.now();
    for (int i=data.length-1;i>=0;i--){
      List info=data[i].split(" ").toList().map((e) =>  int.tryParse(e)!=null?int.parse(e):e).toList();
      DateTime dateTime=new DateTime(info[2],info[1],info[0]);
      if (lasttr.difference(dateTime).inDays>lasttr.weekday){
        weeks.add(new List<int>(8));
        weeks[weeks.length-1]=[0,0,0,0,0,0,0,0];
        weeks[weeks.length-1][0]=dateTime.subtract(Duration(days: dateTime.weekday-1)).day*10000+dateTime.month*100+dateTime.year%100;
      }
      weeks[weeks.length-1>=0?weeks.length-1:0][dateTime.weekday]+=info[isCal?4:5];
      lasttr=dateTime;

    }
    //print(weeks);
    //print(weeks);
    Path customPath = Path()
      ..moveTo(0, 50)
      ..lineTo(MediaQuery.of(context).size.width-60, 50);
    List<Widget> allweeks=new List();
    for (var week in weeks){
      List<Widget> sticks=new List();
      int avg=0,max=0;
      for (int i=1;i<8;i++){
        if (week[i]>max)
          max=week[i];
      }
      for (int i=1;i<8;i++){
        avg+=week[i];

      sticks.add(Column(mainAxisAlignment: MainAxisAlignment.start,children: <Widget>[
          Text(week[i]==0?'':week[i].toString(),style: TextStyle(fontWeight: FontWeight.bold),),
          Container(margin: EdgeInsets.only(bottom: 8,top: 5),width: 10,height: 10+40*week[i]/(max==0?1.0:max),decoration: BoxDecoration(color: (DateTime.now().weekday>=i && week==weeks[0])||week!=weeks[0]?Color.fromARGB(255, 207, 78, 61):Color.fromARGB(100, 207, 78, 61),borderRadius: BorderRadius.all(Radius.circular(20))),),
          Text(days[i-1].substring(0,1),style: TextStyle(fontWeight: FontWeight.bold),),
        (DateTime.now().weekday==i && week==weeks[0])?Icon(Icons.arrow_drop_up,color: Color.fromARGB(255, 207, 78, 67),size: 26,):Text(" ",style: TextStyle(fontSize: 21),),
        ],));
      }
      
      

        allweeks.add(Container(
        decoration: BoxDecoration(color: Colors.white,borderRadius: BorderRadius.all(Radius.circular(20))),
        margin: EdgeInsets.all(14),
        child: Column(children: <Widget>[
          Container(
            decoration: BoxDecoration(color: Color.fromARGB(255, 240, 240, 240),borderRadius: BorderRadius.only(topLeft: Radius.circular(20),topRight: Radius.circular(20))),
            padding: EdgeInsets.all(12),
            child: Row(mainAxisAlignment: MainAxisAlignment.spaceBetween,children: <Widget>[
              Column(crossAxisAlignment: CrossAxisAlignment.start,children: <Widget>[
                Text((week[0]/10000).floor().toString()+' '+(month[DateTime(2000+week[0]%100,(week[0]/100).floor()%100-1,(week[0]/10000).floor()).month])+'-'+(week[0]/10000+6).floor().toString()+' '+(month[DateTime(2000+week[0]%100,(week[0]/100).floor()%100-1,(week[0]/10000).floor()).add(Duration(days: 6)).month]),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 16),),
                Text("20"+(week[0]%100).toString()),
              ],),
              Column(crossAxisAlignment:CrossAxisAlignment.end,children: <Widget>[
                Text(avg.toString(),style: TextStyle(fontSize: 22,fontWeight: FontWeight.bold),),
                Text(AppLocalizations.of(context).translate("avgg")+"("+AppLocalizations.of(context).translate(isCal?"cal":"min")+")")
              ],)
            ],),
          ),
          Padding(
            padding: const EdgeInsets.all(8.0),
            child: Stack(
              children: [Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                crossAxisAlignment: CrossAxisAlignment.end,
                children: sticks,
              ),
                avg!=0.0?DottedBorder(dashPattern: [5],
                  strokeWidth: 1,
                  customPath: (size)=>customPath,
                  color: Colors.grey,
                  child: Container(),):Text("") ],
            ),
          )
        ],),
      ));
    }
    return  Container(child:
        ListView(
          children: allweeks,
        ));
  }
}

class TrainingWeight extends StatefulWidget {
  @override
  _TrainingWeightState createState() => _TrainingWeightState();
}

class _TrainingWeightState extends State<TrainingWeight> with AfterInitMixin{
  int weight;
  String measureW;
  SharedPreferences prefs;
  int goal,start;
  @override
  void didInitState() {
    prefs=Provider.of<Data>(context).prefs;
    getW();
  }
  getW() {

    setState(() {
      weight = prefs.getInt("weight")??50;
      measureW=prefs.getString("measureW")??"kg";
      goal=prefs.getInt("toweight")??-1;
      prefs.containsKey("start")?{}:prefs.setInt("start", weight);
      start=prefs.getInt("start");
    });
  }

  setW() {
    prefs.setInt("weight",weight);
    prefs.setString("measureW", measureW);
    prefs.setInt("toweight", goal);
    prefs.setInt("start", start);
  }
  getWeight(BuildContext context,bool isgoal){
    return
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
                  child: Text(AppLocalizations.of(context).translate(isgoal?"enter":"urw8"),style: TextStyle(fontSize: 20,fontWeight: FontWeight.bold),),
                ),
                WeightPicker(isgoal: isgoal),
                Row(mainAxisAlignment: MainAxisAlignment.spaceEvenly,crossAxisAlignment: CrossAxisAlignment.end,children: <Widget>[
                  SizedBox(
                    width: MediaQuery.of(context).size.width/2-50,
                    child: new OutlineButton(child: new Text(AppLocalizations.of(context).translate(isgoal?"prev":"cancel"),style: TextStyle(fontWeight: FontWeight.bold),),color: Colors.white,onPressed: (){
                      if (!isgoal){setW();Navigator.of(context).pop(false);}else{
                        Navigator.of(context).pop();
                        getWeight(context, false);
                      }
                    },textColor: Colors.black,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(15.0),)),
                  ),
                  SizedBox(
                    width: MediaQuery.of(context).size.width/2-50,
                    child: new FlatButton(child: new Text(AppLocalizations.of(context).translate(isgoal?"sbmt":"next")),color: Color.fromARGB(255, 207, 78, 61),
                        onPressed: (){
                        getW();
                        Navigator.of(context).pop();
                        if (goal==-1)
                        {  start=weight; setW();getW();}

                      if (!isgoal){
                          getWeight(context, true);
                        }else{

                      }
                        //Navigator.pushReplacement(context, new MaterialPageRoute(builder: (context)=>getWeight(context,true)));
                        },textColor: Colors.white,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0))),
                  ),

                ],)
              ],
            ),
          );
        });
  }
  @override
  Widget build(BuildContext context) {
    //prefs.setInt("toweight", -1);
    return Container(margin: EdgeInsets.only(left: 10,right: 10,top: 10),
        child: Material(
          borderRadius: BorderRadius.all(Radius.circular(15)),
          color: Colors.white,
            child:Padding(
              padding: const EdgeInsets.only(left:20.0,right: 20,top:15,bottom: 5),
              child: Column(children: <Widget>[
                Row(children: <Widget>[
                  Icon(Icons.shutter_speed,color: Color.fromARGB(255, 207, 78, 61),size: 20,),
                  Text(" "+AppLocalizations.of(context).translate("w8"),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 18),),
                ],),
                Padding(padding: EdgeInsets.only(top:goal==-1?10:0,bottom: goal==-1?10:0),child: (goal==-1)?Text(AppLocalizations.of(context).translate("entergoal"),style: TextStyle(color: Colors.grey),)
                    :Row(crossAxisAlignment: CrossAxisAlignment.center,
                  children: <Widget>[
                    RichText(text:
                    TextSpan(children:[
                      TextSpan(text:weight.toString(),style: TextStyle(fontSize: 30,fontWeight: FontWeight.bold,color: Colors.black),),
                      TextSpan(text:" "+AppLocalizations.of(context).translate(measureW),style: TextStyle(fontSize: 18,fontWeight: FontWeight.bold,color: Colors.black)),
                      TextSpan(text:" | ",style: TextStyle(fontSize: 20,color: Colors.grey)),
                      TextSpan(text:((weight-goal)>=0?(weight-goal):(weight-goal)*-1).toString()+' '+AppLocalizations.of(context).translate(measureW)+' '+AppLocalizations.of(context).translate("left"),style: TextStyle(fontSize: 14,color: Colors.grey),),
                      ])),
                      Spacer(),
                      CircularPercentIndicator(
                        radius: 50.0,
                        lineWidth: 5.0,
                        percent: ((start-weight)/(start-goal)>0?(start-weight)/(start-goal):0)==0?0.005: ((start-weight)/(start-goal)>0?(start-weight)/(start-goal):0),
                        backgroundColor: Color.fromARGB(255, 230, 230, 230),
                        center: Icon(Icons.shutter_speed,color: Color.fromARGB(255, 207, 78, 61),),
                        progressColor: Color.fromARGB(255, 207, 78, 61),
                      )
                ],)),
                FlatButton(child: Padding(
                  padding: const EdgeInsets.all(8.0),
                  child: Text((goal==-1)?AppLocalizations.of(context).translate("enter").toUpperCase():AppLocalizations.of(context).translate("updgoal").toUpperCase(),style: TextStyle(fontWeight: FontWeight.bold,fontSize: 18)),
                ),color: Color.fromARGB(255, 207, 78, 61),
                    onPressed: (){getWeight(context,false);},
                    textColor: Colors.white,shape:RoundedRectangleBorder(borderRadius: BorderRadius.circular(18.0))),
              ],),
            )
          )
        )
    ;
  }
}
class Settings extends StatefulWidget {
  @override
  _SettingsState createState() => _SettingsState();
}

class _SettingsState extends State<Settings> with AfterInitMixin<Settings>{
  List<Widget> list=new List();
  SharedPreferences prefs;
  List<int> s;
  @override
  void didInitState() {
    prefs=Provider.of<Data>(context).prefs;
    if (!prefs.containsKey('order'))
      prefs.setInt("order", 123);
    s=[(prefs.getInt("order")/100).floor(),(prefs.getInt("order")/10).floor()%10,prefs.getInt("order")%10];
    List<Widget> temp=[Row(children: <Widget>[Icon(Icons.menu),Padding(
      padding: const EdgeInsets.all(10.0),
      child: Icon(Icons.shutter_speed),
    ),Text(AppLocalizations.of(context).translate("w8"))]),
      Row(children: <Widget>[Icon(Icons.menu),Padding(
        padding: const EdgeInsets.all(10.0),
        child: Icon(Icons.directions_run),
      ),Text(AppLocalizations.of(context).translate("tab2"))]),
      Row(children: <Widget>[Icon(Icons.menu),Padding(
        padding: const EdgeInsets.all(10.0),
        child: Icon(Icons.whatshot),
      ),Text(AppLocalizations.of(context).translate("cal"))]),
      ];
    list.add(temp[s[0]-1]);
    list.add(temp[s[1]-1]);
    list.add(temp[s[2]-1]);

  }
  @override
  Widget build(BuildContext context) {

    return Scaffold(
      appBar: AppBar(title: Text(AppLocalizations.of(context).translate("order"),style: TextStyle(color: Colors.black),),backgroundColor: Color.fromARGB(255, 230, 230, 230),iconTheme: IconThemeData(color: Colors.black),),
      body: ReorderableListView(

        padding: EdgeInsets.all(8),
        onReorder: (oldIndex, newIndex){
          setState(() {
            if (newIndex > oldIndex) {
              newIndex -= 1;
            }
            final item = list.removeAt(oldIndex);
            int itemm=s.removeAt(oldIndex);
            list.insert(newIndex, item);
            s.insert(newIndex, itemm);
            prefs.setInt("order", s[0]*100+s[1]*10+s[2]);
          });
        },
        children: list.map((e) => ListTile(key: ValueKey(e),title: e)).toList(),
    ));
  }
}

class Day extends StatefulWidget {
  @override
  _DayState createState() => _DayState();
}
class _DayState extends State<Day> with AfterInitMixin<Day>{
  List<String> data;
  SharedPreferences prefs;
  List<Widget> widgets;
  @override
  void didInitState() {
    prefs=Provider.of<Data>(context).prefs;
    data=Provider.of<Data>(context).trains;
    updWidgets();
  }
  updWidgets(){
    widgets=new List();
    int d=prefs.getInt("order")??123;
    List<Widget> temp=[
      TrainingWeight(),
      TrainingTime(data: data,),
      TrainingCall(data:data)];


      widgets.clear();
      widgets.add(Days(data:data));
      widgets.add(temp[(d/100).floor()-1]);
      widgets.add(temp[(d/10).floor()%10-1]);
      widgets.add(temp[(d%10)-1]);
    setState(() {});
  }

  @override
  Widget build(BuildContext context) {
    //data=Provider.of<Data>(context).trains??[''];
    return Scaffold(
      backgroundColor: Color.fromARGB(255, 230, 230, 230),
      appBar: AppBar(title: Text(AppLocalizations.of(context).translate("tab1").toUpperCase(),style: TextStyle(color: Colors.black, fontWeight: FontWeight.bold,fontSize: 21),),actions: <Widget>[IconButton(icon:Icon(Icons.settings),color: Colors.grey,iconSize: 28,onPressed: ()async {await Navigator.push(context, new MaterialPageRoute(builder: (_)=> Settings()));updWidgets();},)],),
      body: ListView(
        children: widgets,
      ),
    );

  }
}
