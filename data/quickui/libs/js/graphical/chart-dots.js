$(function () {
    // Grab the data
    var data = [],
        axisx = [],
        axisy = [],
        table = $("#for-chart");
    $("tbody td", table).each(function (i) {
        data.push(parseFloat($(this).text(), 10));
    });
    table.hide();
    $("tbody th", table).each(function () {
        axisy.push($(this).text());
    });
    $("tfoot th", table).each(function () {
        axisx.push($(this).text());
    });
    // Draw
    var width = 800,
        height = 300,
        leftgutter = 30,
        bottomgutter = 20,
        r = Raphael("chart", width, height),
        txt = {"font": '10px Fontin-Sans, Arial', stroke: "none", fill: "#000"},
        X = (width - leftgutter) / axisx.length,
        Y = (height - bottomgutter) / axisy.length,
        color = $("#chart").css("color");
        max = Math.round(X / 2) - 1;
    // r.rect(0, 0, width, height, 5).attr({fill: "#000", stroke: "none"});
    for (var i = 0, ii = axisx.length; i < ii; i++) {
        r.text(leftgutter + X * (i + .5), 294, axisx[i]).attr(txt);
    }
    for (var i = 0, ii = axisy.length; i < ii; i++) {
        r.text(10, Y * (i + .5), axisy[i]).attr(txt);
    }
    var o = 0;
    for (var i = 0, ii = axisy.length; i < ii; i++) {
        for (var j = 0, jj = axisx.length; j < jj; j++) {
            var R = data[o] && Math.min(Math.round(Math.sqrt(data[o] / Math.PI) * 4), max);
            if (R) {
                (function (dx, dy, R, value) {
                    var color = ['#2F7ED8','#8BBC21','#FF9C00','#03BDEC','#E00000','#C896FE','#5CD778','#FF8279','#FEB232','#78A4FF','#72BF00'],
                        dt = r.circle(dx + 60 + R, dy + 10, R).attr({stroke: "none", fill: color[R]});
                    if (R < 6) {
                        var bg = r.circle(dx + 60 + R, dy + 10, 6).attr({stroke: "none", fill: "#000", opacity: .4}).hide();
                    }
                    var lbl = r.text(dx + 60 + R, dy + 10, data[o])
                            .attr({"font": '10px "Helvetica Neue", Arial', stroke: "none", fill: "#fff"}).hide();
                    var dot = r.circle(dx + 60 + R, dy + 10, max).attr({stroke: "none", fill: "#000", opacity: 0});
                    dot.hover(function () {
                        if (bg) {
                            bg.show();
                        } else {
                            var clr = Raphael.rgb2hsb(color);
                            clr.b = .5;
                            dt.attr("fill", color[R]);
                        }
                        lbl.show();
                    }, function () {
                        if (bg) {
                            bg.hide();
                        } else {
                            dt.attr("fill", color[R]);
                        }
                        lbl.hide();
                    });
                })(leftgutter + X * (j + .5) - 60 - R, Y * (i + .5) - 10, R, data[o]);
            }
            o++;
        }
    }
});