Ext.define('BrazilJS.view.project.List' ,{
    extend: 'Ext.grid.Panel',
    alias : 'widget.projectList',
    
    //requires: ['Ext.toolbar.Paging'],
    
//    iconCls: 'icon-grid',

    title : '工程',
    store: 'Projects',

    columns: [{
    	header: "序号",
		width: 170,
		flex:1,
		dataIndex: 'id'
	},{
		header: "工程名称",
		width: 160,
		flex:1,
		dataIndex: 'name'
	},{
		header: "备注",
		width: 170,
		flex:1,
		dataIndex: 'content'
    }, {
        header: "计划视图",
        width: 160,
        flex: 1,
        dataIndex: 'id',
        renderer: function (value) {
            return "<a href='" + APIVAR.url.plangantt + "?pid=" + value + "'>" + "计划视图" + "</a>";
        }
    }, {
        header: "跟踪视图",
        width: 160,
        flex: 1,
        dataIndex: 'id',
        renderer: function (value) {
            return [
				"<a href='" + APIVAR.url.jiankeyuangantt + "?pid=" + value + "'>" + "建科院" + "</a>",
				"-",
				"<a href='" + APIVAR.url.gantt + "?pid=" + value + "'>" + "查看" + "</a>"
			].join("");
        }
    }],
	
	initComponent: function() {
		
		this.dockedItems = [{
            xtype: 'toolbar',
            items: [{
//                iconCls: 'icon-save',
                itemId: 'add',
                text: '添加',
                action: 'add'
            },{
//                iconCls: 'icon-delete',
                text: '删除',
                itemId: 'delete',
                action: 'delete'
            },{
//                iconCls: 'icon-delete',
                text: '大数据量例子',
                itemId: 'largedata',
                handler:function(){
            	
            	    window.open("buffered.html");
            	}
            },{
                xtype:'displayfield',
                fieldLabel:'提示',
                labelWidth:50,
                value:'<span style="color:red;">如果数据库无数据或没有配置好，请点<a href="gantt-no-db.html">这里</a>查看文件数据页面。</span>'
            }]
        },
        {
            xtype: 'pagingtoolbar',
            dock:'top',
            store: 'Projects',
            displayInfo: true,
            displayMsg: '工程{0} - {1}   共{2}个工程',
            emptyMsg: "没有工程"
        }];
		
		this.callParent(arguments);
	}
});
