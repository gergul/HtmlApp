Ext.define('BrazilJS.store.Projects', {
    extend: 'Ext.data.Store',
    model: 'BrazilJS.model.Project',
    autoLoad: true,
    pageSize: 35,
    autoLoad: {start: 0, limit: 35},
    
    proxy: {
        type: 'ajax',
        api: {
            read: APIVAR.project.read,
            create: APIVAR.project.create,
            update: APIVAR.project.update,
            destroy: APIVAR.project.destroy
        },
        reader: {
            type: 'json',
            //root: 'data',
            successProperty: 'success'
        },
        writer: {
            type: 'json',
            writeAllFields: true,
            //root: 'data',
            allowSingle: false,
            encode: false
           
        },
        listeners: {
            exception: function(proxy, response, operation){
                Ext.MessageBox.show({
                    title: 'REMOTE EXCEPTION',
                    msg: '请求数据失败，可能原因为数据库没有配置好。请配置好数据库连接后再刷新本页面。现将跳转到文件数据页面。',
                    icon: Ext.MessageBox.ERROR,
                    buttons: Ext.Msg.OK,
                    fn:function(){
                    	window.location.href='gantt-no-db.html';
                    }
                });
            }
        }
    }
});