Raphael.fn.pieChart = function (cx, cy, r, values, labels, stroke) {
    var paper = this,
        rad = Math.PI / 180,
        chart = this.set();
    function sector(cx, cy, r, startAngle, endAngle, params) {
        var x1 = cx + r * Math.cos(-startAngle * rad),
            x2 = cx + r * Math.cos(-endAngle * rad),
            y1 = cy + r * Math.sin(-startAngle * rad),
            y2 = cy + r * Math.sin(-endAngle * rad);
        return paper.path(["M", cx, cy, "L", x1, y1, "A", r, r, 0, +(endAngle - startAngle > 180), 0, x2, y2, "z"]).attr(params);
    }
    var angle = 0,
        total = 0,
        start = 0,
        process = function (j) {
            var value = values[j],
                angleplus = 180 * value / total,
                popangle = angle + (angleplus / 2),
                color = Raphael.hsb(start, .75, 1),
                ms = 500,
                delta = 30,
//              bcolor = Raphael.hsb(start, 1, 1),
                bcolor = ['#3399ff','#00cc66','#ff9900','#03BDEC','#ff5500','#C896FE','#5CD778','#FF8279','#FEB232','#78A4FF','#72BF00'],
                p = sector(cx, cy, r, angle, angle + angleplus, {fill: bcolor[j], stroke: stroke, "stroke-width": 1}),
                txt = paper.text(cx + (r - 40) * Math.cos(-popangle * rad), cy + (r -40) * Math.sin(-popangle * rad), labels[j]).attr({fill: "#ffffff", stroke: "none", opacity: 0, "font-size": 20});
            p.mouseover(function () {
                p.stop().animate({transform: "s1.1 1.1 " + cx + " " + cy}, ms, "elastic");
                txt.stop().animate({opacity: 1}, ms, "elastic");
            }).mouseout(function () {
                p.stop().animate({transform: ""}, ms, "elastic");
                txt.stop().animate({opacity: 0}, ms);
            });
            angle += angleplus;
            chart.push(p);
            chart.push(txt);
            start += .1;
        };
    for (var i = 0, ii = values.length; i < ii; i++) {
        total += values[i];
    }
    for (i = 0; i < ii; i++) {
        process(i);
    }
    return chart;
};

$(function () {
    var values = [],
        labels = [];
    $("tr").each(function () {
        values.push(parseInt($("td", this).text(), 10));
        labels.push($("th", this).text());
    });
    $("table").hide();
    var R=Raphael("holder", 500, 500);
    R.pieChart(350, 350, 200, values, labels, "#fff");
    R.circle(350,350 ,100).attr({fill: "#ffffff", "stroke-width": 0});
    R.text(350 , 350,"语言流行度").attr({fill: "#000000", stroke: "none", opacity: 1, "font-size": 20});
    R.setViewBox(0, 0, 400, 600);
});