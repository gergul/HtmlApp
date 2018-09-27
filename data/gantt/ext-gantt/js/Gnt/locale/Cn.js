/*

Ext Gantt 2.2.21
Copyright(c) 2009-2014 Bryntum AB
http://bryntum.com/contact
http://bryntum.com/license

*/
Ext.define('Gnt.locale.Cn', {
    extend      : 'Sch.locale.Locale',
    requires    : 'Sch.locale.En',
    singleton   : true,

    l10n        : {
        'Gnt.util.DurationParser' : {
            unitsRegex : {	
				MILLI       : /^ms$|^\u6BEB\u79D2/i,
				SECOND      : /^s$|^\u79D2/i,
				MINUTE      : /^m$|^\u5206/i,
				HOUR        : /^h$|^hr$|^\u5C0F\u65F6/i,
				DAY         : /^d$|^\u5929/i,
				WEEK        : /^w$|^wk|^\u5468/i,
				MONTH       : /^mo|^\u6708/i,
				QUARTER     : /^q$|^quar|^\u5B63\u5EA6/i,
				YEAR        : /^y$|^yr|^\u5E74/i
            }
        },

        'Gnt.field.Duration' : {
            invalidText : "错误的工期值"
        },

        'Gnt.feature.DependencyDragDrop' : {
            fromText    : '从',
            toText      : '到',
            startText   : '开始',
            endText     : '结束'
        },


        'Gnt.Tooltip' : {
            startText       : '开始: ',
            endText         : '结束: ',
            durationText    : '工期: '
        },

        'Gnt.plugin.TaskContextMenu' : {
            taskInformation     : '任务信息...',
            newTaskText         : '新建任务',
            deleteTask          : '删除任务',
            editLeftLabel : '修改左边标签',
            editRightLabel : '修改右边标签',
            add : '添加...',
            deleteDependency : '删除前后置关系...',
            addTaskAbove : '到上方',
            addTaskBelow : '到下方',
            addMilestone : '里程碑',
            addSubtask :'子节点',
            addSuccessor : '后继任务',
            addPredecessor : '前置任务',
			
            convertToMilestone  : '转换为里程碑',
            convertToRegular    : '转化为常规任务'      
        },

        'Gnt.plugin.DependencyEditor' : {

			fromText : '从',
            toText : '到',
            typeText : '类型',
            lagText : '延迟',
            endToStartText : '结束开始',
            startToStartText : '开始开始',
            endToEndText : '结束结束',
            startToEndText : '开始结束'
        },

        'Gnt.widget.calendar.Calendar' : {
            dayOverrideNameHeaderText : '名称',
            overrideName        : '名称',
            startDate           : '开始时间',
            endDate             : '结束时间',
            error               : '错误',
			
            dateText           : '日期',
            addText            : '添加',
            editText           : '编辑',
            removeText         : '删除',
            workingDayText     : '工作日',
            weekendsText       : '周末',
            overriddenDayText   : '特殊天',
            overriddenWeekText  : '特殊周',
			
            workingTimeText    : '工作时间',
            nonworkingTimeText : '非工作时间',
            dayOverridesText   : '过载的天',
            weekOverridesText  : '过载的周',
            okText             : '确定',
            cancelText         : '取消',
            parentCalendarText : '父日历',
            noParentText       : '无父日历',
            selectParentText   : '请选择父日历',
            newDayName         : '[未命名]',
            calendarNameText   : '日历名称',
            tplTexts            : {
                tplWorkingHours : '工时',
                tplIsNonWorking : '非工作的',
                tplOverride     : '过载',
                tplInCalendar   : '在日历中',
                tplDayInCalendar: '日历中标准天',
                tplBasedOn      : '基于'
            },
            overrideErrorText   : '日期被定义过',
            overrideDateError   : '该日期被特殊的周定义过: {0}',
            startAfterEndError  : '开始时间应该小于结束时间',
            weeksIntersectError : '周定义不能交叉'
        },
		

        'Gnt.widget.calendar.AvailabilityGrid' : {
            startText           : '开始',
            endText             : '结束',
            addText             : '添加',
            removeText          : '删除',
            error               : '错误'
        },

        'Gnt.widget.calendar.DayEditor' : {
            workingTimeText     : 'Working time',
            nonworkingTimeText  : 'Non-working time'
        },

        'Gnt.widget.calendar.WeekEditor' : {
            defaultTimeText     : '默认时间',
            workingTimeText     : '工作时间',
            nonworkingTimeText  : '非工作时间',
            error               : '错误',
            noOverrideError     : "特别周定义只能包含默认天 - 不能保存"
        },

        'Gnt.widget.calendar.ResourceCalendarGrid' : {
            name        : '名称',
            calendar    : '日历'
        },

        'Gnt.widget.calendar.CalendarWindow' : {
            ok      : '确定',
            cancel  : '取消'
        },

        'Gnt.field.Assignment' : {
            cancelText : '取消',
            closeText  : '保存并关闭'
        },

        'Gnt.column.AssignmentUnits' : {
            text : '单位'
        },

        'Gnt.column.Duration' : {
            text : '工期'
        },

        'Gnt.column.Effort' : {
            text : '工时'
        },

        'Gnt.column.EndDate' : {
            text : '结束'
        },

        'Gnt.column.PercentDone' : {
            text : '% 完成'
        },

        'Gnt.column.ResourceAssignment' : {
            text : '分配的资源'
        },

        'Gnt.column.ResourceName' : {
            text : '资源名称'
        },

        'Gnt.column.SchedulingMode' : {
            text : '模式'
        },

        'Gnt.column.Predecessor' : {
            text : '前置任务'
        },

        'Gnt.column.Successor' : {
            text : '后继任务'
        },

        'Gnt.column.StartDate' : {
            text : '开始'
        },

        'Gnt.column.WBS' : {
            text : 'WBS'
        },

        'Gnt.column.Sequence' : {
            text : '编号'
        },

        'Gnt.widget.taskeditor.TaskForm' : {
            taskNameText            : '名称',
            durationText            : '工期',
            datesText               : '日期',
            baselineText            : '基线',
            startText               : '开始',
            finishText              : '结束',
            percentDoneText         : '完成百分比',
            baselineStartText       : '开始',
            baselineFinishText      : '结束',
            baselinePercentDoneText : '完成百分比',
            effortText              : '工时',
            invalidEffortText       : '错误的投入值',
            calendarText            : '日历',
            schedulingModeText      : '排程模式'
        },

        'Gnt.widget.DependencyGrid' : {
			idText                      : 'ID编号',
			snText                      : '序号',
            taskText                    : '任务名称',
            blankTaskText               : '请选择任务',
            invalidDependencyText       : '错误的依赖关系',
            parentChildDependencyText   : '父子节点含有依赖关系',
            duplicatingDependencyText   : '有重复的依赖关系',
            transitiveDependencyText    : '存在传递的依赖关系',
            cyclicDependencyText        : '依赖关系中存在环路',
            typeText                    : '类型',
            lagText                     : '延隔时间',
            clsText                     : 'CSS类',
            endToStartText              : '结束开始',
            startToStartText            : '开始开始',
            endToEndText                : '结束结束',
            startToEndText              : '开始结束'
        },

        'Gnt.widget.AssignmentEditGrid' : {
            confirmAddResourceTitle : '确认',
            confirmAddResourceText  : '未找到{0}相关资源。要新建该资源?',
            noValueText             : '请选择要分配的资源。',
            noResourceText          : '未找到{0}相关资源。'
        },

        'Gnt.widget.taskeditor.TaskEditor' : {
            		
			generalText         : '常规',
            resourcesText       : '资源',
            dependencyText      : '前置任务',
            addDependencyText   : '添加',
            dropDependencyText  : '删除',
            notesText           : '备注',
            advancedText        : '高级',
            wbsCodeText         : 'WBS代码',
            addAssignmentText   : '添加',
            dropAssignmentText  : '删除'
        },

        'Gnt.plugin.TaskEditor' : {
            title           : '任务信息',
            alertCaption    : '信息',
            alertText       : '请在保存前修改相关的错误',
            okText          : '确定',
            cancelText      : '取消'
        },

        'Gnt.field.EndDate' : {
            endBeforeStartText : '结束时间早于开始时间'
        },

        'Gnt.column.Note'   : {
            text            : '备注'
        },

        'Gnt.column.AddNew' : {
            text            : '添加新列...'
        },

        'Gnt.column.EarlyStartDate' : {
            text            : '最早开始'
        },

        'Gnt.column.EarlyEndDate' : {
            text            : '最早结束'
        },

        'Gnt.column.LateStartDate' : {
            text            : '最晚开始'
        },

        'Gnt.column.LateEndDate' : {
            text            : '最晚结束'
        },

        'Gnt.field.Calendar' : {
            calendarNotApplicable : '任务日历和资源日历无交叉'
        },

        'Gnt.column.Slack' : {
            text            : '余量'
        },

        'Gnt.column.Name'   : {
            text            : '任务名称'
        },

        'Gnt.column.BaselineStartDate'   : {
            text            : '计划开始时间'
        },

        'Gnt.column.BaselineEndDate'   : {
            text            : '计划结束时间'
        },

        'Gnt.column.Milestone'   : {
            text            : '里程碑'
        },

        'Gnt.field.Milestone'   : {
            yes             : '是',
            no              : '否'
        },

        'Gnt.field.Dependency'  : {
            invalidFormatText       : '无效的依赖关系',
            invalidDependencyText   : '检测出无效的依赖关系, 请确认是否有依赖的环路',
            invalidDependencyType   : '无效的依赖类型 {0}. 只允许: {1}.'
        }
    }
});
