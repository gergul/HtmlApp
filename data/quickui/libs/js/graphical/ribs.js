jQuery.fn.ribs = function(data) {
    var My = {
        // 财产类型：房产、车辆、银行、土地、地税、国税、工商
        lx : [ {
            type : 'fc',
            name : '房产',
            color : '#84DDDE',
            icon : ''
        }, {
            type : 'cl',
            name : '车辆',
            color : '#84DDDE',
            icon : ''
        }, {
            type : 'yh',
            name : '银行',
            color : '#84DDDE',
            icon : ''
        }, {
            type : 'td',
            name : '土地',
            color : '#84DDDE',
            icon : ''
        }, {
            type : 'swGs',
            name : '国税',
            color : '#84DDDE',
            icon : ''
        }, {
            type : 'swDs',
            name : '地税',
            color : '#84DDDE',
            icon : ''
        }, {
            type : 'gs',
            name : '工商',
            color : '#84DDDE',
            icon : ''
        } ],
        // 常量
        consts : {
            // 财产子项
            colControlled : 'colControlled',
            colUncontrolled : 'colUncontrolled',
            // 数目总和
            controlled : 'controlled',
            uncontrolled : 'uncontrolled'
        },
        page : {
            rowcount : 4, // 每页显示个数
            datasize : data.length, // 数据个数
            pagecount : data.length % 4 == 0 ? parseInt(data.length / 4)
                    : (parseInt(data.length / 4) + 1)
        // 页数
        }
    };
    var panel = $(this);
    /** 入口 */
    (function() {
        var ribs = $("<div class='ribs'></div>");
        // ribs.children().remove();
        var wrap = $("<div class='ribs-wrap'></div>");
        wrap.append(addColControlled()); // 左
        wrap.append(addColPerson(data)); // 中
        wrap.append(addColUncontrolled()); // 右
        wrap.appendTo(ribs);
        $(panel).append(ribs);

        // 图标位置调整-平均分布-需设置在翻页效果前
        fixWindow();
        // 翻页效果
        jQuery(".colPerson").slide({ // 父容器
            titCell : ".hd ul", // 箭头所在容器
            mainCell : ".content ul", // 内容容器
            autoPage : true,
            effect : "top",
            scroll : My.page.rowcount, // 滚动个数
            autoPlay : false, // 自动播放
            vis : My.page.rowcount
        // 可见个数
        });
        // 总线-需放在“翻页效果”后
        $(ribs).append(addYAxis());
        // 监听事件
        addAllEventListener();
        $(".ribs").children(".ribs-wrap").append(addYAxis());
    })();
    /** 清除样式 */
    function clearStyle() {
        $(".colPerson ul li").removeClass('active').find(".active")
                .removeClass("active");
        $(".colControlled ul li").removeClass('active');
        $(".colUncontrolled ul li").removeClass('active');
        // 移除所有的线
        $(".ribs canvas").remove();
    }
    ;
    function fixWindow(){
        /**财产子项图表平均分布 */
        var h_parent = $(panel).height();//父容器高度
        var h_li = $(".colControlled ul li").height();//每个财产子项的高度
        var n = $(".colControlled ul li").length;//财产子项个数
        var marginTop_li = (h_parent - h_li*n)/(n+1);
        $(".colControlled ul li").css("margin-top",marginTop_li+"px");
        $(".colUncontrolled ul li").css("margin-top",marginTop_li+"px");
        
        /**中心轴高度*/
        var h_content = h_parent-$(".colPerson .hd").height()*2-40;
        $(".colPerson .content").height(h_content);
        
        /**中心轴人平均分布 需设置在翻页效果前*/
        var h_li_person = $(".colPerson .content ul li").height();
//        var n_person = $(".colPerson .content ul li").length;
        var n_person = My.page.datasize<=My.page.rowcount?My.page.datasize:My.page.rowcount;//每页显示个数 不超过4个
        var marginTop_li_person =( h_content-h_li_person*n_person)/(n_person+1);
        $(".colPerson .content ul li").css("margin-top",marginTop_li_person+"px");
    }
    /** 绑定事件 */
    function addAllEventListener() {
        // 人员单击事件
        $(".ribs .colPerson .content ul li .name").delegate(
                ".text",
                "click",
                function(a, b, c) {
                    // 清除样式
                    clearStyle();
                    // 人员样式
                    $(this).offsetParent().addClass("active");
                    $(this).addClass("active");
                    // 同级的左边数字 点击事件
                    colControl_click(My.consts.colControlled, $(this)
                            .offsetParent().children('.controlled'));
                    // 同级的右边数字点击事件
                    colControl_click(My.consts.colUncontrolled, $(this)
                            .offsetParent().children('.uncontrolled'));
                });
        // 数量（已被控制财产）单击事件 - 财产细项点亮并显示数字
        $(".ribs .colPerson .content ul li").delegate(".count.controlled",
                "click", function() {
                    colControl_click(My.consts.colControlled, this);
                });
        // 数量（未被控制财产）单击事件
        $(".ribs .colPerson .content ul li").delegate(".count.uncontrolled",
                "click", function() {
                    colControl_click(My.consts.colUncontrolled, this);
                });
        // 翻页
        $(".ribs .colPerson .hd ").delegate('a', 'click', function() {
            // 隐藏连线-图表设置为未激活状态
            $(".ribs canvas").hide();
            $(".colControlled ul li").removeClass("active");
            $(".colUncontrolled ul li").removeClass("active");
            if (isBackToPosition(this)) {
                // 调用数字点击事件-显示连线和点亮财产子项
                setTimeout(function() {
                    $(".colPerson .content li.active .count.active").click();
                }, 200);
            }
        });
    }
    ;
    /**
     * 财产子项 （交互方式）<BR>
     * 
     * @param container
     *            容器名称
     * @param this_
     *            单击对象
     */

    function colControl_click(container, this_) {
        // colControlled/colUncontrolled
        var className = '.' + container;
        if ($(this_).offsetParent().hasClass("active")) {
            // 点击的总数，对应的当事人，为active状态
            // 设置财产子项状态
            // 判断财产子项是否为active，是，则移除active（不显示数据）
            var len1 = $("." + container + " ul li[class*=active]").length;
            if (len1 > 0) {
                $(this_).removeClass("active");
                // 移除数字  动画效果.title
                $(className + " ul li").find(".title").animate({"width":"0"},function(){
                    // 移除icon（自己和子节点的）active
                    $(className + " ul li").removeClass("active").find(".active")
                    .removeClass("active");
                });
                // 移除（自己和子节点的）active
//                $(className + " ul li").removeClass("active").find(".active")
//                        .removeClass("active");
                // 如果两边收起，则人名处于未选中状态
                var theother = (container == My.consts.colControlled) ? My.consts.colUncontrolled
                        : My.consts.colControlled;
                var len2 = $("." + theother + " ul li[class*=active]").length;
                if (len2 == 0) {
                    $("myCanvas_" + theother).remove();
                    $(".colPerson ul li").removeClass('active').find(".active")
                            .removeClass("active");
                    removeLine(theother);
                }
                removeLine(container);
            } else {
                // 否则，添加样式active（显示数据）
                var mydata = $(this_).data("mydata");
                setColControlActived(container, mydata);
                setTimeout(function(){
                    
                    drawLine(container, this_);
                },500);
                // 数字加active
                $(this_).addClass("active");
                // 财产子项 添加单击事件
            }
        } else {
            // 点击的总数，对应的当事人，为非active状态时
            clearStyle();
            // 移除所有的线
            // 财产子项
            var mydata = $(this_).data("mydata");
            setColControlActived(container, mydata);
            // 当事人加active
            $(this_).addClass("active").offsetParent().addClass('active');
            // 数字加active
            setTimeout(function(){
                
                drawLine(container, this_);
            },1000);
        }
    }
    ;
    /**
     * 左右两侧财产小项的active样式
     * 
     * @param container
     *            容器的类样式名称
     * @param mydata
     *            数据
     */
    function setColControlActived(container, tempdata) {
        $(this).addClass("active");
        if (tempdata == null) {
            return;
        }
        var mydata = new Object();
        if (container == My.consts.colControlled) {
            mydata = tempdata.controlled;
        } else {
            mydata = tempdata.uncontrolled
        }
        var dsr = tempdata.dsr;

        var className = "." + container;
        // .colControlled ul li
        $(className + " ul li").find(".title").animate({"width":"0"});//隐藏数字
        $(className + " ul li").removeClass("active");
        var dsrData = $.each(mydata, function(type, value) {
            // .ribs .colControlled ul li.fc
            var item = $(".ribs " + className + " ul li." + type);
            item.data('mydata', {
                type : type,
                value : value,
                dsrmc : dsr.name,
                sfzjhm : dsr.sfzjhm
            });
            //显示数字和财产类别
            // 设置.num数字内容，设置.title动画效果
            $(item).find(".title .num").html(value);
            $(item).find(".title").animate({"width":autoWidth(value)});
            item.addClass("active");
        });
    }
    ;
    /**需求要求默认留三位数宽度，超出后自动延伸*/
    function autoWidth(num){
        var width = 40;
        var numLength = num.toString().length;
        if(num==null||numLength<=3){
            return width+"px";
        }
        
        var fontsize = 10;
        width += fontsize*(numLength-3);
        return width+"px";
    };
    /** y轴线，上下按钮 */
    function addYAxis() {
        var yAxis = $("<div class='yAxis'></div>");
        var content = $(".ribs .colPerson .content");
        $(yAxis.height($(content).height()
                + parseInt($(content).css("padding")) * 2));
        $(content).append(yAxis);
    }
    /** 1.colControlled 左测 以控制财产列 */
    function addColControlled() {
        /** 1.colControlled */
        var colControlled = $("<div class='colControlled'></div>");
        var ul = $("<ul></ul>");
        // 遍历数组
        $.each(My.lx, function() {
            var type = this.type;
            var name = this.name;
            var title = this.title;

            var li = $("<li class='" + type + "'></li>");
            var spanIcon = $("<span class='icon fr'></span>");
            var spanTitle = $("<span class='title fr'><span class='name'>" + name + "</span><span class='num'></span></span>");
            li.append(spanIcon).append(spanTitle);
            li.appendTo(ul);
        });
        colControlled.append(ul);
        return colControlled;
    }
    ;
    /** 3.addColUncontrolled 右侧为控制财产项 */

    function addColUncontrolled() {
        var colUncontrolled = $("<div class='colUncontrolled'></div>");
        var ul = $("<ul></ul>");
        // 遍历数组
        $.each(My.lx, function() {
            var type = this.type;
            var name = this.name;
            var li = $("<li class='" + type + "'></li>");
            var spanIcon = $("<span class='icon fl'></span>");
            var spanTitle = $("<span class='title fl '><span class='name'>" + name + "</span><span class='num'></span></span>");
            li.append(spanIcon).append(spanTitle);
            li.appendTo(ul);
        });
        colUncontrolled.append(ul);
        return colUncontrolled;
    }
    ;
    /** 2.colPerson 中间人名列 */

    function addColPerson(data) {
        /** 2.colPerson */
        // 1 父容器
        var colPerson = $("<div class='colPerson'></div>");
        // 2 标题
//        var title = $("<div class='title clearfix'></div>");
        // 3 上一页
        var prev = $("<div class='hd'><span class='title'>已扩展业务</span><a class='prev'></a><span  class='title'>未扩展业务</span></div>");
        // 4 内容 自动生成
        var content = $("<div class='content'></div>");
        var ul = $("<ul></ul>")
        $.each(data, function() {
            var name = this.dsr.name;
            var countControlled = getCount(this.controlled);
            var countUncontrolled = getCount(this.uncontrolled);

            var liItem = $("<li></li>");
            var countSpan_controlled = $("<span class='count controlled'>"
                    + countControlled + "</span>");
            var nameSpan = $("<span class='name'/>").append(
                    "<span class='text text-overflow-fag'>" + name + "</span>");
            var countSpan_uncontrolled = $(
                    "<span>" + countUncontrolled + "</span>").addClass("count")
                    .addClass("uncontrolled");
            // 绑定数据
            countSpan_controlled.data('mydata', this);
            nameSpan.children(".text").data('mydata', this); // 人名绑定数据
            countSpan_uncontrolled.data('mydata', this);

            liItem.append(countSpan_controlled).append(nameSpan).append(
                    countSpan_uncontrolled);
            liItem.appendTo(ul);

        });
        content.append(ul);
        // 5 下一页
        var next = $("<div class='hd'><a class='next'></a></div>");

//        colPerson.append(title).append(prev).append(content).append(next);
        colPerson.append(prev).append(content).append(next);
        return colPerson;
    }
    ;
    /** 累加 */
    function getCount(obj) {
        var sum = 0;
        if (obj == null) {
            return 0;
        } else {
            $.each(obj, function(a, num) {
                sum += num;
            });
            return sum;
        }
    }
    /** 画线 */
    function drawLine(type, obj) {
        var className = 'myCanvas_' + type;
        // 1.创建canvas
        var ribs = $(".ribs");
        $(ribs).children("." + className).remove();
        var canvas = document.createElement('canvas');

        canvas.className = className;
        $(canvas).attr({
            'width' : ribs.width()*0.95,//0.95防止canvas层太高显示滚动条
            'height' : ribs.height()*0.95,
            'data-curscrolltop' : $(".ribs .colPerson .content ul").css('top')
            // 翻页时隐藏，翻回来显示
        });
        // 2.添加到dom
        $(".ribs").append($(canvas));
        // 3.ie8 初始化设置
        var DEFAULT_VERSION = "8.0";
        var ua = navigator.userAgent.toLowerCase();
        var isIE = ua.indexOf("msie") > -1;
        var safariVersion;
        if (isIE) {
            safariVersion = ua.match(/msie ([\d.]+)/)[1];
            if (parseInt(safariVersion) <= parseInt(DEFAULT_VERSION)) {
                canvas = window.G_vmlCanvasManager.initElement(canvas);
            }
        }
        var myCanvas = $("." + className)[0];
        var context = myCanvas.getContext("2d");

        // 4.画线

        // 4.1
        if ($(obj).hasClass(My.consts.controlled)) {
            // 左边连线
            lineLeft(obj, context);
        } else if ($(obj).hasClass(My.consts.uncontrolled)) {
            // 右边连线
            lineRight(obj, context);
        }

        context.stroke();
    }

    function lineLeft(obj, context) {
        // 点击的数字位置
        var formOffset = $(obj).offset();
        formOffset.top -= num($('.ribs'), 'marginTop');//如果报错找不到top属性，是因为封装数据的type在My.lx里不存在
        formOffset.left -= num($('.ribs'), 'marginLeft');
        var fromX = formOffset.left;
        var fromY = formOffset.top + $(obj).height() / 2;

        var mydata = $(obj).data('mydata');
        // 数据
        var data_controlled = mydata.controlled;
        if (data_controlled == null || data_controlled.length == 0) {
            return;
        }
        // 左侧各图位置
        $.each(data_controlled, function(a, b) {
            var icon = $(".colControlled ." + a + " .icon");
            // x = icon.left + icon.width
            var offset = icon.offset();
            offset.top -= num($('.ribs'), 'marginTop');
            offset.left -= num($('.ribs'), 'marginLeft');
            // var x = offset.left + icon.width() + 10;
            // var y = offset.top + icon.height() / 2 + 5;
            var x = offset.left + icon.width();
            var y = offset.top + icon.height() / 2;
            context.strokeStyle = "#DBDBDB";
            context.lineWidth = 1;
            context.moveTo(x, y);

            context.lineTo(fromX, fromY);
        });
    }

    function lineRight(obj, context) {
        // 点击的数字位置
        var formOffset = $(obj).offset();
        formOffset.top -= num($('.ribs'), 'marginTop');
        formOffset.left -= num($('.ribs'), 'marginLeft');
        var fromX = formOffset.left + $(obj).width();
        var fromY = formOffset.top + $(obj).height() / 2;

        var mydata = $(obj).data('mydata');
        // 数据
        var data_controlled = mydata.uncontrolled;
        if (data_controlled == null || data_controlled.length == 0) {
            return
        }
        // 左侧各图位置
        $.each(data_controlled, function(a, b) {
            var icon = $(".colUncontrolled ." + a + " .icon");
            // x = icon.left + icon.width
            var offset = icon.offset();
            offset.top -= num($('.ribs'), 'marginTop');
            offset.left -= num($('.ribs'), 'marginLeft');
            // var x = offset.left - 10;
            // var y = offset.top + icon.height() / 2 + 5;
            var x = offset.left;
            var y = offset.top + icon.height() / 2;
            context.strokeStyle = "#DBDBDB";
            context.lineWidth = 1;
            context.moveTo(x, y);

            context.lineTo(fromX, fromY);
        });
    }

    function num(obj, property) {
        return parseInt(obj.css(property));
    }
    ;

    function removeLine(type) {
        var className = 'myCanvas_' + type;
        $(".ribs").children("." + className).remove();
    }
    ;
    /** 翻页，根据canvas属性上记录的top值，和下一步达到的top值比较，判断是否为上次点击的页面 */
    function isBackToPosition(this_) {
        var canvasTop = parseInt($(".ribs canvas").attr("data-curscrolltop")); // 被点击时top值
        var curScrollTop = parseInt($(".ribs .colPerson .content ul")
                .css("top")); // 当前top值
        var perScrollHeight = $(".ribs .colPerson .tempWrap").height(); // 每次滚动的高度

        if ($(this_).hasClass("prev")) {
            if (curScrollTop + perScrollHeight == canvasTop) {
                return true;
            }
        } else if ($(this_).hasClass("next")) {
            var maxScroll = perScrollHeight * My.page.pagecount;
            if (curScrollTop - perScrollHeight == canvasTop
                    || (canvasTop == 0 && Math.abs(curScrollTop
                            - perScrollHeight) == maxScroll)) {
                return true;
            }
        }

    }
}