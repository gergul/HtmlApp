var APIVAR = {
    dependency: {
        read: 'handler/DependencyController.aspx?action=read',
        create: 'handler/DependencyController.aspx?action=create',
        destroy: 'handler/DependencyController.aspx?action=destroy',
        update: 'handler/DependencyController.aspx?action=update'
    },
    task: {
        read: 'handler/TaskController.aspx?action=read',
        create: 'handler/TaskController.aspx?action=create',
        destroy: 'handler/TaskController.aspx?action=destroy',
        update: 'handler/TaskController.aspx?action=update'
    },
    project: {
        read: 'handler/ProjectController.aspx?action=read',
        create: 'handler/ProjectController.aspx?action=create',
        destroy: 'handler/ProjectController.aspx?action=destroy',
        update: 'handler/ProjectController.aspx?action=update'
    },
    url: {
        gantt: "Gantt.aspx",
        plangantt: "PlanGantt.aspx",
        jiankeyuangantt:"JiankeyuanGantt.aspx",
        upload: ""
    }

}

/*如果采用web service的方式， 可以使用以下的配置*/
//var APIVAR = {
//	dependency:	{
//            read: 'webservices/Dependencies.asmx/Get',
//            create: 'webservices/Dependencies.asmx/Create',
//            destroy: 'webservices/Dependencies.asmx/Delete',
//            update: 'webservices/Dependencies.asmx/Update'
//    },
//    task: {
//        read: 'webservices/Tasks.asmx/Get',
//        create: 'webservices/Tasks.asmx/Create',
//        destroy: 'webservices/Tasks.asmx/Delete',
//        update: 'webservices/Tasks.asmx/Update'
//    },
//    project: {
//        read: 'webservices/Projects.asmx/Get',
//        create: 'webservices/Projects.asmx/Create',
//        destroy: 'webservices/Projects.asmx/Delete',
//        update: 'webservices/Projects.asmx/Update'
//    }
//    
//}
