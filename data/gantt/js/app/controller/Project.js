Ext.define('BrazilJS.controller.Project', {
	
	    extend: 'Ext.app.Controller',

    stores: ['Projects'],

    models: ['Project'],

    views: ['project.Edit', 'project.List'],

    refs: [{
            ref: 'mygrid',
            selector: 'grid'
        }
    ],

    init: function() {
        this.control({
            'projectList dataview': {
                itemdblclick: this.editUser
            },
            'projectList button[action=add]': {
            	click: this.editUser
            },
            'projectList button[action=delete]': {
                click: this.deleteUser
            },
            'projectEdit button[action=save]': {
                click: this.updateUser
            }
        });
    },

    editUser: function(grid, record) {
        var edit = Ext.create('BrazilJS.view.project.Edit').show();
        
        if(record){
        	edit.down('form').loadRecord(record);
        }
    },
    
    updateUser: function(button) {
        var win    = button.up('window'),
            form   = win.down('form'),
            record = form.getRecord(),
            values = form.getValues();
        
        
		if (values.id > 0){
			record.set(values);
		} else{
			record = Ext.create('BrazilJS.model.Project');
			record.set(values);
			//不能设置id， 不然url会选择update 而不是create
            //record.set("id", 0);
			//record.setId(0);
			this.getProjectsStore().add(record);
		}
        
		win.close();
        this.getProjectsStore().sync();
    },
    
    deleteUser: function() {
    	var grid = this.getMygrid();
    	record = grid.getSelectionModel().getSelection(); 
        store = this.getProjectsStore();
	    store.remove(record);
	    
	    this.getProjectsStore().sync();
    }
});
