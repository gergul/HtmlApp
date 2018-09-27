/**
 * English translations for the Scheduler component
 *
 * NOTE: To change locale for month/day names you have to use the corresponding Ext JS language file.
 */
Ext.define('Sch.locale.Cn', {
    extend      : 'Sch.locale.Locale',
    singleton   : true,

    l10n        : {
        'Sch.util.Date' : {
            unitNames : {
                YEAR        : { single : '年',    plural : '年',   abbrev : '年' },
                QUARTER     : { single : '季', plural : '季',abbrev : '季' },
                MONTH       : { single : '月',   plural : '月',  abbrev : '月' },
                WEEK        : { single : '周',    plural : '周',   abbrev : '周' },
                DAY         : { single : '天',     plural : '天',    abbrev : '天' },
                HOUR        : { single : '时',    plural : '时',   abbrev : '时' },
                MINUTE      : { single : '分',  plural : '分', abbrev : '分' },
                SECOND      : { single : '秒',  plural : '秒', abbrev : '秒' },
                MILLI       : { single : '毫秒',      plural : '毫秒',      abbrev : '毫秒' }
            }
        },

        'Sch.view.SchedulerGridView' : {
            loadingText : '加载中...'
        },

        'Sch.plugin.CurrentTimeLine' : {
            tooltipText : '当前时间'
        },

        'Sch.plugin.EventEditor' : {
            saveText    : '保存',
            deleteText  : '删除',
            cancelText  : '取消'
        },

        'Sch.plugin.SimpleEditor' : {
            newEventText    : '预定...'
        },

        'Sch.widget.ExportDialog' : {
            generalError                : '有错误发生, 稍后再试.',
            title                       : '导出设置',
            formatFieldLabel            : '页面格式',
            orientationFieldLabel       : '方向',
            rangeFieldLabel             : '导出范围',
            showHeaderLabel             : '添加页数',
            orientationPortraitText     : '纵向',
            orientationLandscapeText    : '横向',
            completeViewText            : '完成时间表',
            currentViewText             : '当前视图',
            dateRangeText               : '日期范围',
            dateRangeFromText           : '导出从',
            pickerText                  : '调整行/列到指定值',
            dateRangeToText             : '到',
            exportButtonText            : '导出',
            cancelButtonText            : '取消',
            progressBarText             : '导出...',
            exportToSingleLabel         : '导出为单页面',
            adjustCols                  : '调整列宽',
            adjustColsAndRows           : '调整列宽和行高',
            specifyDateRange            : '指定日期范围'
        },

        // -------------- View preset date formats/strings -------------------------------------
        'Sch.preset.Manager' : function () {
            var M = Sch.preset.Manager,
                vp = M.getPreset("hourAndDay");

            if (vp) {
                vp.displayDateFormat = 'g:i A';
                vp.headerConfig.middle.dateFormat = 'g A';
                vp.headerConfig.top.dateFormat = 'Y年m月d日';
            }

            vp = M.getPreset("secondAndMinute");
            if (vp) {
                vp.displayDateFormat = 'g:i:s';
                vp.headerConfig.top.dateFormat = 'D, d g:iA';
            }


            vp = M.getPreset("dayAndWeek");
            if (vp) {
                vp.displayDateFormat = 'm/d h:i A';
                vp.headerConfig.middle.dateFormat = 'Y年m月d日';
                vp.headerConfig.top.renderer = function (start, end, cfg) {
                    var w = start.getWeekOfYear();
                    return 'w.' + ((w < 10) ? '0' : '') + w + ' ' + Sch.util.Date.getShortMonthName(start.getMonth()) + ' ' + start.getFullYear();
                };
            } 

            vp = M.getPreset("weekAndDay");
            if (vp) {
                vp.displayDateFormat = 'm月d日';
                vp.headerConfig.bottom.dateFormat = 'm月d日';
                vp.headerConfig.middle.dateFormat = 'Y年m月d日';
            }

            vp = M.getPreset("weekAndMonth");
            if (vp) {
                vp.displayDateFormat = 'Y年m月d日';
                vp.headerConfig.middle.dateFormat = 'm月d日';
                vp.headerConfig.middle.renderer = function (start, end, cfg) {
                    cfg.align = 'left';
                    return Ext.Date.format(start, 'm月d日');
                };
                vp.headerConfig.top.dateFormat = 'Y年m月d日';

            } 

            vp = M.getPreset("weekAndDayLetter");
            if (vp) {
                vp.displayDateFormat = 'm月d日';
                vp.headerConfig.bottom.dateFormat = 'M月d日';
                vp.headerConfig.bottom.renderer = function (start, end, cfg) {
                    //将星期一变为一
                    return Ext.Date.dayNames[start.getDay()].substr(2, 1);
                };
                vp.headerConfig.middle.dateFormat = 'Y年m月d日';
            }

            vp = M.getPreset("weekDateAndMonth");
            if (vp) {
                vp.displayDateFormat = 'Y年m月d日';
                vp.headerConfig.middle.dateFormat = 'm月d日';
                vp.headerConfig.middle.renderer = function (start, end, cfg) {
                    cfg.align = 'left';
                    return Ext.Date.format(start, 'm月d日');
                };
                vp.headerConfig.top.dateFormat = 'Y年m月d日';

            } 

            vp = M.getPreset("monthAndYear");
            if (vp) {
                vp.displayDateFormat = 'Y年m月d日';
                vp.headerConfig.middle.dateFormat = 'Y年m月';
                vp.headerConfig.top.dateFormat = 'Y年';
            } 

            vp = M.getPreset("year");
            if (vp.year) {
                vp.displayDateFormat = 'Y年m月d日';
                vp.headerConfig.bottom.renderer = function (start, end, cfg) {
                    return Ext.String.format('{0}季度', Math.floor(start.getMonth() / 3) + 1);
                };
                vp.headerConfig.middle.dateFormat = 'Y年';
            } 

            vp = M.getPreset("manyYears");
            if (vp) {
                vp.displayDateFormat = 'Y-m-d';
                vp.headerConfig.middle.dateFormat = 'Y';
            }
        }
    }
});
