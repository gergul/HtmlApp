/*
* 北京龙搏中科软件有限公司
* 龙搏方案网 http://www.fanganwang.com
* authored by 程晓
* 该文件定义了TaskStore类， Dependency类，产生了Gantt的实例
*  DemoGanttPanel中一个复杂甘特图的类， 该文件只是将他实例化
*/

Ext.ns('App');
Ext.BLANK_IMAGE_URL = "ext-min/resources/themes/images/default/tree/s.gif";


//Ext.require([
//    'MyApp.DemoGanttPanel'
//]);

/*
 * 汉化 界面，
 * 汉化 面板，
 * 小图标
 * 导入导出
 * 之前的grid
 * dirty图标
 * 
 * */

Ext.ns("Longboo");

Ext.define('Longboo.TaskContextMenu', {
    extend     : 'Gnt.plugin.TaskContextMenu', 
  	triggerEvent : 'itemcontextmenu',
  	
    createMenuItems : function () {
        return this.callParent().concat({
            text        : '显示到当前任务',
            
            handler     : this.onMyHandler,
            scope       : this
        })
    },
    
    onMyHandler : function () {
        // the task on which the right click have occured
        var task        = this.rec;
        // this.grid.taskStore.remove(selected.getRange());
        //滚动到某个任务
        this.grid.getSchedulingView().scrollEventIntoView(task, true);
    }
});

Ext.onReady(function() {
    Ext.QuickTips.init();
    //Localize();
	
    App.Gantt.init();
});



App.Gantt = {

    // Initialize application
    init: function (serverCfg) {
        this.gantt = this.createGantt();

        var vp = Ext.create("Ext.Viewport", {
            layout: 'border',
            items: [
            /*{
            region      : 'north',
            contentEl   : 'north',
            bodyStyle   : 'padding:15px'
            },*/
                this.gantt
            ]
        });
    },

    createGantt: function () {

        /*Ext.define('MyTaskModel', {
            extend: 'Gnt.model.Task',

            //todo:尚未实现
            isMilestone: function () {
                return this.get('Milestone');
            },
            percentDoneField: 'percent_done',
            //nameField: 'name',

            baselineStartDateField: 'baseline_start_date',
            baselineEndDateField: 'baseline_end_date',

            durationField: 'duration',
            durationUnitField: 'duration_unit',

            startDateField: 'start_date',
            endDateField: 'end_date',


            //使用customableField 的方式， 可以让数据按照原来的方式提交
            //例如：baseline_start_date:'xxxx' , 而不是BaselineStartDate:'xxxxx'
            //但是id和name字段居然不行， 难道是不区分大小写？？


            fields: [
                { name: 'Id', mapping:'id', type: 'int', useNull: true },
                { name: 'percent_done', type: 'int' },
                { name:"Name", mapping: 'name' },
                 { name: 'priority', type: 'int', defaultValue: 1 },

                { name: 'baseline_start_date', type: 'date', dateFormat: 'c' },
                { name: 'baseline_end_date', type: 'date', dateFormat: 'c' },

                { name: 'parent_id', type: 'int' },
                { name: 'duration', type: 'float' },
                { name: 'duration_unit' },

                { name: 'other_field', persist: true },

                 { name: 'pid', type: 'int', persist: true },
                  { name: 'index', type: 'int', persist: true },

                { name: 'start_date', type: 'date', dateFormat: 'c' },
                { name: 'end_date', type: 'date', dateFormat: 'c' }
            ]
        });*/

        Ext.define('MyTaskModel', {
            extend: 'Gnt.model.Task',

            //todo:尚未实现
            isMilestone: function () {
                return this.get('Milestone');
            },
            //这里使用mapping比使用XXXField也许要好

            fields: [
                { name: 'Id', mapping:"id", type: 'int', useNull: true },
                { name: 'PercentDone', mapping: 'percent_done', type: 'int' },
                { name:"Name", mapping: 'name' },
                { name: 'priority', type: 'int' },

                { name: "BaselineStartDate", mapping: 'baseline_start_date', type: 'date', dateFormat: 'c', persist: true },
                { name: "BaselineEndDate", mapping: 'baseline_end_date', type: 'date', dateFormat: 'c', persist: true },

                //这个在任务升级降级中有非常重要的作用
                //parentId的p注意是小写
                { name: 'parentId',mapping: 'parent_id', type: 'int' },
                { name: 'Duration', mapping: 'duration', type: 'float' },
                { name: 'DurationUnit', mapping: 'duration_unit', persist: true },

                { name: 'other_field', persist: true },

                 { name: 'pid', type: 'int', persist: true },
                 { name: 'index', type: 'int', persist: true },

                { name: 'StartDate', mapping: 'start_date', type: 'date', dateFormat: 'c', persist: true },
                { name: 'EndDate', mapping: 'end_date', type: 'date', dateFormat: 'c', persist: true },
                
                //标记行的颜色
                { name: 'TaskColor', persist: false }
            ]
        });


        var taskStore = Ext.create("Gnt.data.TaskStore", {
            model: 'MyTaskModel',
            //sorters : 'StartDate',
            autoSync: true, //自动保存
            proxy: {
                type: 'ajax',
                headers: { "Content-Type": 'application/json' },
                api: APIVAR.task,
                extraParams: { pid: pid },
                writer: {
                    type: 'json',
                    encode: false,
                    //让post back的数据按照mapping的值回写
                    nameProperty: 'mapping',
                    allowSingle: false
                },
                reader: {
                    type: 'json'
                }
            }
        });

        Ext.define('MyDependencyModel', {
            extend: 'Gnt.model.Dependency',

            //这里使用mapping比使用XXXField也许要好

            fields: [
                { name: 'Id', mapping:"id", type: 'int', useNull: true },
                { name: 'From', mapping: 'from_id', type: 'int' },
                { name: 'To', mapping: 'to_id', type: 'int' },
                { name: "Type", mapping: 'type', type:'int' },
                { name: 'pid', type: 'int' }
            ]
        });

        //任务和任务之间的关系
        var dependencyStore = Ext.create("Gnt.data.DependencyStore", {
            model: 'MyDependencyModel',
            autoLoad: true,
            autoSync: true, //自动保存
            proxy: {
                type: 'ajax',
                headers: { "Content-Type": 'application/json' },
                method: 'GET',
                reader: {
                    type: 'json'
                },
                writer: {
                    type: 'json',
                    encode: false,
                    //让post back的数据按照mapping的值回写
                    nameProperty: 'mapping',
                    allowSingle: false
                },
                extraParams: { pid: pid },
                api: APIVAR.dependency
            }
        });

        var resourceStore = Ext.create("Gnt.data.ResourceStore", {
            autoLoad: true,
            proxy: {
                type: 'memory'
            }
        });


        var assignmentStore = Ext.create("Gnt.data.AssignmentStore", {
            autoLoad: true,
            resourceStore: resourceStore,
            proxy: {
                type: 'memory'
            }
        });

        var start = new Date(2012, 0, 1);
        var g = Ext.create("MyApp.DemoGanttPanel", {
            region: 'center',
            selModel: new Ext.selection.TreeModel({ ignoreRightMouseSelection: false, mode: 'MULTI' }),
            taskStore: taskStore,
            dependencyStore: dependencyStore,

            resourceStore: resourceStore,
            assignmentStore: assignmentStore,
            //snapToIncrement : true,    // Uncomment this line to get snapping behavior for resizing/dragging.
            columnLines: true,


            startDate: g_start,
            endDate: g_end,


            viewPreset: 'weekAndDayLetter',

            // Add some extra functionality
            plugins: [
        	          Ext.create("Longboo.TaskContextMenu"),
        	          //bufferedrenderer在没有数据的情况下， 会导致以下的错误， 暂时注释掉
        	          //Cannot read property 'parentNode' of undefined
        	          //{ ptype: 'bufferedrenderer' },
            //Ext.create("Sch.plugin.Pan"),
        	          Ext.create('Sch.plugin.TreeCellEditing', { clicksToEdit: 2 }),
        	          this.taskEditor = Ext.create('Gnt.plugin.TaskEditor')
        	]


        });

        g.on({
            /*dependencydblclick : function(ga, rec) {
            var from    = taskStore.getNodeById(rec.get('From')).get('Name'),
            to      = taskStore.getNodeById(rec.get('To')).get('Name');
                    
            Ext.Msg.alert('Hey', Ext.String.format('You clicked the link between "{0}" and "{1}"', from, to));
            },*/
            timeheaderdblclick: function (col, start, end) {
                Ext.Msg.alert('Hey', 'You click header cell : ' + Ext.Date.format(start, 'Y-m-d') + ' - ' + Ext.Date.format(end, 'Y-m-d'));
            },
            scope: this
        });

        return g;
    }
};

