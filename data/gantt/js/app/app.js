Ext.onReady(function(){
	Ext.BLANK_IMAGE_URL = "ext-min/resources/themes/images/default/tree/s.gif";
	Ext.application({
	    name: 'BrazilJS',

	    controllers: [
	        'Project'
	    ],
		paths:{
		    'BrazilJS': 'js/app' // This is set by default, Ext.layout.container.Container will be
		                // loaded from ./layout/Container.js
		},
	    launch: function() {
	        Ext.create('Ext.container.Viewport', {
	            layout: 'fit',
	            items: [
	                {
	                    xtype: 'projectList'
	                }
	            ]
	        });
	    }
	});		
});
