function drawRectProgress(paper,current,min,max,x,y,width,param,paramBg,fun){
    var borderRadius=4;
    if(broswerFlag=="IE7"||broswerFlag=="IE8"){
        borderRadius=0;
    }
    paper.rect(x, y, width,1,borderRadius).attr(paramBg)
    var rect=paper.rect(x, y, 0,1,borderRadius).attr(param);
    rect.animate({width:current/(max-min)*width}, 900,"<",fun);
    return rect;
}
function drawRingProgress(paper,current,min,max,cx,cy,radius,param,paramBg,fun){
    paper.circle(cx, cy, radius).attr(paramBg)
    var ring=paper.path().attr(param).attr({arc: [min, max,cx,cy,radius]});
    ring.animate({arc: [current, max,cx,cy,radius]}, 900,"<",fun);
    return ring;
}
function drawRingProgress2(paper,current1,current2,current3,min,max,cx,cy,radius,param1,param2,param3){
    var ring3=paper.path().attr(param3).attr({arc: [min, max,cx,cy,radius]});
    ring3.animate({arc: [current1+current2+current3, max,cx,cy,radius]}, 900,"<");
    
    var ring2=paper.path().attr(param2).attr({arc: [min, max,cx,cy,radius]});
    ring2.animate({arc: [current1+current2, max,cx,cy,radius]}, 900,"<");

    var ring=paper.path().attr(param1).attr({arc: [min, max,cx,cy,radius]});
    ring.animate({arc: [current1, max,cx,cy,radius]}, 900,"<",function(){
         var x1=getArcNewPos(current1/2,max,cx,cy,radius).posx;
        var y1=getArcNewPos(current1/2,max,cx,cy,radius).posy;
        paper.path(["M", x1, y1, "L", x1+50, y1-50, "L", x1+80, y1-50]).attr({stroke: "#3399ff", "stroke-width": 1})
        paper.text(x1+70 , y1-65,current1+"%").attr({fill: "#3399ff", stroke: "none", opacity: 1, "font-size": 14});

        var x2=getArcNewPos(current1+current2/2,max,cx,cy,radius).posx;
        var y2=getArcNewPos(current1+current2/2,max,cx,cy,radius).posy;
        paper.path(["M", x2, y2, "L", x2+50, y2+50, "L", x2+80, y2+50]).attr({stroke: "#1fc695", "stroke-width": 1})
        paper.text(x2+70 , y2+35,current2+"%").attr({fill: "#1fc695", stroke: "none", opacity: 1, "font-size": 14});

        var x3=getArcNewPos(current1+current2+current3/2,max,cx,cy,radius).posx;
        var y3=getArcNewPos(current1+current2+current3/2,max,cx,cy,radius).posy;
        paper.path(["M", x3, y3, "L", x3-50, y3-50, "L", x3-80, y3-50]).attr({stroke: "#ff9900", "stroke-width": 1})
        paper.text(x3-70 , y3-65,current3+"%").attr({fill: "#ff9900", stroke: "none", opacity: 1, "font-size": 14});

    });
}
function drawRingProgress3(paper,current,min,max,cx,cy,radius,param,paramBg,fun){
    //paper.circle(cx, cy, radius).attr(paramBg)
    var ring=paper.path().attr(param).attr({arc: [min, max,cx,cy,radius]});
    ring.animate({arc: [current, max,cx,cy,radius]}, 900,"<",fun);

    var ring2=paper.path().attr(paramBg).attr({arc: [min, max,cx,cy,radius+10]});
    ring2.animate({arc: [current, max,cx,cy,radius+10]}, 900,"<");
    return ring;
}
function getArcNewPos(value, total, cx,cy,R) {
        var alpha = 360 / total * value,
            a = (90 - alpha) * Math.PI / 180,
            x = cx + R * Math.cos(a),
            y = cy - R * Math.sin(a);
        
        return {posx: x,posy:y};
};
function initPaper(id,width,height){
    var r = Raphael(id, width, height);
    r.customAttributes.arc = function (value, total, cx,cy,R) {
        var alpha = 360 / total * value,
            a = (90 - alpha) * Math.PI / 180,
            x = cx + R * Math.cos(a),
            y = cy - R * Math.sin(a),
            path;
        if (total == value) {
            path = [["M", cx, cy - R], ["A", R, R, 0, 1, 1, cx-0.01, cy - R]];
        } else {
            path = [["M", cx, cy - R], ["A", R, R, 0, +(alpha > 180), 1, x, y]];
        }
        return {path: path};
    };
    
    return r;
}
