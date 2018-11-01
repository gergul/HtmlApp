var sNodes=[
	{ "id":"1", "parentId":"0", "name":"表单","url":"guide1.html", "isParent": "true","icon": "./skin/index_icon.png","backgroundPosition":"-111px -48px"},
	
	{ "id":"101", "parentId":"1", "name":"表单元素","icon": "./skin/index_icon.png","backgroundPosition":"-111px -48px"},
	{ "id":"1101", "parentId":"101", "name":"文本框","url":"../../sample_html/form/textinput-password.html", "target":"frmright","title":"textinput/password","icon": "./skin/index_icon.png","backgroundPosition":"-160px -48px"},
	{ "id":"1102", "parentId":"101", "name":"文本域","url":"../../sample_html/form/textarea.html", "target":"frmright","title":"textarea","icon": "./skin/index_icon.png","backgroundPosition":"-96px -48px"},
	{ "id":"1103", "parentId":"101", "name":"基本按钮","url":"../../sample_html/form/button.html", "target":"frmright","title":"button","icon": "./skin/index_icon.png","backgroundPosition":"-128px -48px"},
	{ "id":"1104", "parentId":"101", "name":"单选按钮","url":"../../sample_html/form/radio.html", "target":"frmright","title":"radio","icon": "./skin/index_icon.png","backgroundPosition":"-209px -48px"},
	{ "id":"1105", "parentId":"101", "name":"多选按钮","url":"../../sample_html/form/checkbox.html", "target":"frmright","title":"checkbox","icon": "./skin/index_icon.png","backgroundPosition":"-176px -32px"},
	{ "id":"1106", "parentId":"101", "name":"单选下拉框*","url":"../../sample_html/form/select-single.html", "target":"frmright","title":"select","icon": "./skin/index_icon.png","backgroundPosition":"-157px -81px"},
	{ "id":"1107", "parentId":"101", "name":"过滤下拉框*","url":"../../sample_html/form/select-suggestion.html", "target":"frmright","title":"selectSuggestion","icon": "./skin/index_icon.png","backgroundPosition":"-157px -81px"},
	{ "id":"1108", "parentId":"101", "name":"树形下拉框*","url":"../../sample_html/form/select-tree.html", "target":"frmright","title":"selectTree","icon": "./skin/index_icon.png","backgroundPosition":"-157px -81px"},
	{ "id":"1109", "parentId":"101", "name":"多选下拉框*","url":"../../sample_html/form/select-multi.html", "target":"frmright","title":"selectTree multi","icon": "./skin/index_icon.png","backgroundPosition":"-157px -81px"},
	{ "id":"1110", "parentId":"101", "name":"组合下拉框*","url":"../../sample_html/form/select-custom.html", "target":"frmright","title":"selectCustom","icon": "./skin/index_icon.png","backgroundPosition":"-157px -81px"},
	{ "id":"1112", "parentId":"101", "name":"自动提示框*","url":"../../sample_html/form/suggestion.html", "target":"frmright","title":"suggestion","icon": "./skin/index_icon.png","backgroundPosition":"-172px -81px"},
	{ "id":"1113", "parentId":"101", "name":"日期选择器","url":"../../sample_html/form/date.html", "target":"frmright","title":"date","icon": "./skin/index_icon.png","backgroundPosition":"-144px -48px"},
	{ "id":"1114", "parentId":"101", "name":"双向选择器*","url":"../../sample_html/form/lister.html", "target":"frmright","title":"lister","icon": "./skin/index_icon.png","backgroundPosition":"-48px -48px"},
	{ "id":"1115", "parentId":"101", "name":"树形双选器*","url":"../../sample_html/form/lister-tree.html", "target":"frmright","title":"listerTree","icon": "./skin/index_icon.png","backgroundPosition":"-48px -48px"},
	{ "id":"1116", "parentId":"101", "name":"颜色选择器","url":"../../sample_html/form/color.html", "target":"frmright","title":"color","icon": "./skin/index_icon.png","backgroundPosition":"-64px -48px"},
	{ "id":"1117", "parentId":"101", "name":"数字步进器","url":"../../sample_html/form/stepper.html", "target":"frmright","title":"stepter","icon": "./skin/index_icon.png","backgroundPosition":"-193px -48px"},
	{ "id":"1118", "parentId":"101", "name":"软键盘控件","url":"../../sample_html/form/keypad.html", "target":"frmright","title":"keypad","icon": "./skin/index_icon.png","backgroundPosition":"-32px -48px"},
	{ "id":"1119", "parentId":"101", "name":"评星级控件","url":"../../sample_html/form/rating.html", "target":"frmright","title":"rating","icon": "./skin/index_icon.png","backgroundPosition":"-16px -48px"},
	{ "id":"1120", "parentId":"101", "name":"异步上传控件*","url":"../../sample_html/form/fileupload.html", "target":"frmright","title":"fileUpload","icon": "./skin/index_icon.png","backgroundPosition":"0px -48px"},
	{ "id":"1121", "parentId":"101", "name":"上传文件列表*","url":"../../sample_html/form/filelist.html", "target":"frmright","title":"fileList","icon": "./skin/index_icon.png","backgroundPosition":"0px -48px"},
	{ "id":"1122", "parentId":"101", "name":"同步上传控件*","url":"../../sample_html/form/file.html", "target":"frmright","title":"file","icon": "./skin/index_icon.png","backgroundPosition":"0px -48px"},
	{ "id":"1123", "parentId":"101", "name":"条件过滤器1*","url":"../../sample_html/form/filter.html", "target":"frmright","title":"filter","icon": "./skin/index_icon.png","backgroundPosition":"-207px -32px"},
	{ "id":"1124", "parentId":"101", "name":"条件过滤器2","url":"../../sample_html/form/condition.html", "target":"frmright","title":"condition","icon": "./skin/index_icon.png","backgroundPosition":"-207px -32px"},
	{ "id":"1125", "parentId":"101", "name":"条件过滤器3","url":"../../sample_html/form/condition-nav.html", "target":"frmright","title":"conditionNav","icon": "./skin/index_icon.png","backgroundPosition":"-207px -32px"},
	
	{ "id":"102", "parentId":"1", "name":"综合表单","icon": "./skin/index_icon.png","backgroundPosition":"-208px -64px"},
	{ "id":"1201", "parentId":"102", "name":"表单布局","url":"../../sample_html/fullform/layout.html", "target":"frmright","title":"table","icon": "./skin/index_icon.png","backgroundPosition":"-178px -64px"},
	{ "id":"1202", "parentId":"102", "name":"表单验证*","url":"../../sample_html/fullform/validation.html", "target":"frmright","title":"validation","icon": "./skin/index_icon.png","backgroundPosition":"-114px -66px"},
	{ "id":"1203", "parentId":"102", "name":"表单验证-直接提示*","url":"../../sample_html/fullform/validation2.html", "target":"frmright","title":"validation","icon": "./skin/index_icon.png","backgroundPosition":"-114px -66px"},
	{ "id":"1204", "parentId":"102", "name":"表单响应式布局","url":"../../sample_html/fullform/layout-auto.html", "target":"frmright","title":"formLayout","icon": "./skin/index_icon.png","backgroundPosition":"-192px -64px"},
	{ "id":"1205", "parentId":"102", "name":"表单拆分","url":"../../sample_html/fullform/step.html", "target":"frmright","title":"stepForm","icon": "./skin/index_icon.png","backgroundPosition":"-161px -64px"},
	{ "id":"1206", "parentId":"102", "name":"异步提交*","url":"../../sample_html/fullform/submit-ajax.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-130px -64px"},
	{ "id":"1207", "parentId":"102", "name":"异步弹窗提交","url":"../../sample_html/fullform/submit-ajax-pop.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-130px -64px"},
	{ "id":"1208", "parentId":"102", "name":"异步编辑-标签赋值*","url":"../../sample_html/fullform/edit-ajax-tag.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-112px -32px"},
	{ "id":"1209", "parentId":"102", "name":"异步编辑-数据赋值*","url":"../../sample_html/fullform/edit-ajax-notag.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-112px -32px"},
	{ "id":"1210", "parentId":"102", "name":"动态创建表单并赋值","url":"../../sample_html/fullform/create-form.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-145px -64px"},
	{ "id":"1211", "parentId":"102", "name":"条件过滤器综合示例1","url":"../../sample_html/fullform/filter-demo.html", "target":"frmright","title":"filter","icon": "./skin/index_icon.png","backgroundPosition":"-207px -32px"},
	{ "id":"1212", "parentId":"102", "name":"条件过滤器综合示例2","url":"../../sample_html/fullform/condition-demo.html", "target":"frmright","title":"condition","icon": "./skin/index_icon.png","backgroundPosition":"-207px -32px"},
	{ "id":"1213", "parentId":"102", "name":"条件过滤器综合示例3","url":"../../sample_html/fullform/condition-nav-demo.html", "target":"frmright","title":"conditionNav","icon": "./skin/index_icon.png","backgroundPosition":"-207px -32px"},
	
	
	
	
	
	{ "id":"2", "parentId":"0", "name":"表格","url":"guide2.html","icon": "./skin/index_icon.png","backgroundPosition":"-48px -64px"},
	
	{ "id":"201", "parentId":"2", "name":"grid基础示例","icon": "./skin/index_icon.png","backgroundPosition":"-48px -64px"},
	{ "id":"2101", "parentId":"201", "name":"使用url*","url":"../../sample_html/datagrid/basic-url.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2102", "parentId":"201", "name":"使用远程data*","url":"../../sample_html/datagrid/basic-data.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2103", "parentId":"201", "name":"使用本地数据","url":"../../sample_html/datagrid/basic-local.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2104", "parentId":"201", "name":"分页记忆行号","url":"../../sample_html/datagrid/rownumber-memory.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2105", "parentId":"201", "name":"长文本提示","url":"../../sample_html/datagrid/longtext.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2106", "parentId":"201", "name":"内容格式化","url":"../../sample_html/datagrid/format.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2107", "parentId":"201", "name":"对行列渲染","url":"../../sample_html/datagrid/render.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2108", "parentId":"201", "name":"锁定列","url":"../../sample_html/datagrid/lock.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2109", "parentId":"201", "name":"单元格操作","url":"../../sample_html/datagrid/cell.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2110", "parentId":"201", "name":"弹窗中的表格","url":"../../sample_html/datagrid/basic-pop.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2111", "parentId":"201", "name":"分页记忆选中项","url":"../../sample_html/datagrid/checkrows-memory.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2112", "parentId":"201", "name":"动态选中","url":"../../sample_html/datagrid/checkrows.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2132", "parentId":"201", "name":"点击行选中","url":"../../sample/datagrid/checkrows-click.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2113", "parentId":"201", "name":"表格动态操作","url":"../../sample_html/datagrid/dynamic.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2114", "parentId":"201", "name":"动态切换表格","url":"../../sample_html/datagrid/change-grid.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2115", "parentId":"201", "name":"动态设置url*","url":"../../sample_html/datagrid/seturl.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2116", "parentId":"201", "name":"滚动条位置","url":"../../sample_html/datagrid/scroll-to.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2117", "parentId":"201", "name":"滚动到特定行","url":"../../sample_html/datagrid/scroll-to-row.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2118", "parentId":"201", "name":"工具栏","url":"../../sample_html/datagrid/toolbar.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2119", "parentId":"201", "name":"表格右键菜单","url":"../../sample_html/datagrid/context-menu.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2120", "parentId":"201", "name":"表头过滤","url":"../../sample_html/datagrid/head-filter.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2121", "parentId":"201", "name":"复杂表头","url":"../../sample_html/datagrid/multiheader.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2122", "parentId":"201", "name":"不显示表头","url":"../../sample_html/datagrid/noheader.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2131", "parentId":"201", "name":"大数据测试","url":"../../sample_html/datagrid/large-data.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},

	{ "id":"205", "parentId":"2", "name":"grid其他模式","icon": "./skin/index_icon.png","backgroundPosition":"-50px 0px"},
	{ "id":"2123", "parentId":"205", "name":"树形表格*","url":"../../sample_html/datagrid/treegrid.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2124", "parentId":"205", "name":"树形表格-个性设置","url":"../../sample_html/datagrid/treegrid-dynamic.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2125", "parentId":"205", "name":"树形表格-异步加载*","url":"../../sample_html/datagrid/treegrid-ajax.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2126", "parentId":"205", "name":"父子表格*","url":"../../sample_html/datagrid/detailgrid.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2210", "parentId":"205", "name":"父子表-操作子表*","url":"../../sample_html/datagrid/detailgrid-edit.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2211", "parentId":"205", "name":"父子表-自定义内容","url":"../../sample_html/datagrid/detailgrid-custom.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2212", "parentId":"205", "name":"父子表-自定义样式","url":"../../sample_html/datagrid/detailgrid-style.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2127", "parentId":"205", "name":"分组展现","url":"../../sample_html/datagrid/group.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2128", "parentId":"205", "name":"分组展现-完整示例","url":"../../sample_html/datagrid/group-autowidth.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2129", "parentId":"205", "name":"数据汇总","url":"../../sample_html/datagrid/summary.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2130", "parentId":"205", "name":"表格分组+汇总","url":"../../sample_html/datagrid/group-summary.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},

	

	{ "id":"202", "parentId":"2", "name":"grid综合示例","icon": "./skin/index_icon.png","backgroundPosition":"-50px 0px"},
	
	{ "id":"2201", "parentId":"202", "name":"自定义样式","url":"../../sample_html/datagrid/custom-style.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2202", "parentId":"202", "name":"跨列附加一行","url":"../../sample_html/datagrid/append-row.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2203", "parentId":"202", "name":"单元格信息提示","url":"../../sample_html/datagrid/cell-tip.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2204", "parentId":"202", "name":"选中显示条件","url":"../../sample_html/datagrid/auto-condition.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2205", "parentId":"202", "name":"点击单元格展开详情","url":"../../sample_html/datagrid/cell-detail.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2206", "parentId":"202", "name":"打开选项卡查看详情","url":"../../sample_html/datagrid/cell-detail2.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2207", "parentId":"202", "name":"表格双选器(小型)*","url":"../../sample_html/datagrid/lister-grid.html", "target":"frmright","title":"listerGrid","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2208", "parentId":"202", "name":"表格双选器(左右满屏)*","url":"../../sample_html/datagrid/lister-grid2.html", "target":"frmright","title":"listerGrid","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2209", "parentId":"202", "name":"表格双选器(上下满屏)*","url":"../../sample_html/datagrid/lister-grid3.html", "target":"frmright","title":"listerGrid","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2213", "parentId":"202", "name":"最大化表格","url":"../../sample_html/datagrid/max-grid.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},	
	{ "id":"2214", "parentId":"202", "name":"列数定制","url":"../../sample_html/datagrid/column-order.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2215", "parentId":"202", "name":"数据筛选","url":"../../sample_html/datagrid/grid-condition.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2232", "parentId":"202", "name":"数据筛选2","url":"../../sample_html/datagrid/grid-filter.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2216", "parentId":"202", "name":"双表格","url":"../../sample_html/datagrid/two-grid.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2217", "parentId":"202", "name":"表格与卡片切换","url":"../../sample_html/datagrid/grid-card.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},


		
	
	{ "id":"203", "parentId":"2", "name":"table表格*","icon": "./skin/index_icon.png","backgroundPosition":"-97px -64px"},
	{ "id":"2301", "parentId":"203", "name":"特性举例","url":"../../sample_html/table/guide.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2302", "parentId":"203", "name":"多表头示例","url":"../../sample_html/table/multiheader.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2303", "parentId":"203", "name":"表格动态操作","url":"../../sample_html/table/dynamic.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2304", "parentId":"203", "name":"树形表格*","url":"../../sample_html/table/treetable.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2305", "parentId":"203", "name":"父子表格*","url":"../../sample_html/table/detailtable.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	
	

	{ "id":"207", "parentId":"2", "name":"数据打印", "isParent": "true","icon": "./skin/index_icon.png","backgroundPosition":"-155px -97px"},
	{ "id":"2701", "parentId":"207", "name":"列表打印","url":"../../sample_html/datagrid/print-grid.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"2702", "parentId":"207", "name":"表格打印","url":"../../sample_html/datagrid/print-table.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},


	
	{ "id":"3", "parentId":"0", "name":"导航与布局","url":"guide3.html", "isParent": "true","icon": "./skin/index_icon.png","backgroundPosition":"-180px 0px"},
	{ "id":"401", "parentId":"3", "name":"提示类组件","icon": "./skin/index_icon.png","backgroundPosition":"-50px -16px"},
	{ "id":"4101", "parentId":"401", "name":"提示 toast","url":"../../sample_html/popup/toast.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-66px 0px"},
	{ "id":"4102", "parentId":"401", "name":"通知 notice","url":"../../sample_html/popup/notice.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-113px -16px"},
	{ "id":"4103", "parentId":"401", "name":"消息 message","url":"../../sample_html/popup/message.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-98px -0px"},
	{ "id":"4104", "parentId":"401", "name":"鼠标提示 tooltip","url":"../../sample_html/popup/tooltip.html", "target":"frmright","title":"title","icon": "./skin/index_icon.png","backgroundPosition":"-97px -16px"},
	{ "id":"4105", "parentId":"401", "name":"弹窗 dialog","url":"../../sample_html/popup/dialog.html", "target":"frmright","title":"Dialog","icon": "./skin/index_icon.png","backgroundPosition":"-66px -16px"},
	
	
	{ "id":"302", "parentId":"3", "name":"导航组件","icon": "./skin/index_icon.png","backgroundPosition":"-195px 0px"},
	{ "id":"3201", "parentId":"302", "name":"弹出菜单","url":"../../sample_html/nav/menu-popup.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-186px -81px"},
	{ "id":"3202", "parentId":"302", "name":"右键菜单","url":"../../sample_html/nav/menu-rightclick.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-16px -16px"},
	{ "id":"3203", "parentId":"302", "name":"基本选项卡","url":"../../sample_html/nav/tab-basic.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-32px -80px"},
	{ "id":"3204", "parentId":"302", "name":"基本选项卡-样式2","url":"../../sample_html/nav/tab-basic-modern.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-32px -80px"},
	{ "id":"3205", "parentId":"302", "name":"基本选项卡-流程","url":"../../sample_html/nav/tab-basic-process.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-32px -80px"},
	{ "id":"3206", "parentId":"302", "name":"动态选项卡","url":"../../sample_html/nav/tab-dynamic.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-32px -80px"},
	{ "id":"3207", "parentId":"302", "name":"抽屉容器","url":"../../sample_html/nav/accordion.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-96px -80px"},
	{ "id":"3208", "parentId":"302", "name":"图标工具栏","url":"../../sample_html/nav/icon-toolbar.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-80px -80px"},
	{ "id":"3209", "parentId":"302", "name":"数字分页控件","url":"../../sample_html/nav/paging-number.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-120px -81px"},
	{ "id":"3210", "parentId":"302", "name":"箭头分页控件","url":"../../sample_html/nav/paging-arrow.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"0px -80px"},
		
	
	{ "id":"301", "parentId":"3", "name":"树组件*","icon": "./skin/index_icon.png","backgroundPosition":"0px -32px"},
	{ "id":"3101", "parentId":"301", "name":"基本使用*","url":"../../sample_html/tree/basic.html", "target":"frmright","title":"基本使用","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3102", "parentId":"301", "name":"异步加载数据*","url":"../../sample_html/tree/async.html", "target":"frmright","title":"异步加载数据","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3103", "parentId":"301", "name":"添加复选框","url":"../../sample_html/tree/checktree.html", "target":"frmright","title":"添加复选框","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3104", "parentId":"301", "name":"树的拖拽","url":"../../sample_html/tree/dragdrop.html", "target":"frmright","title":"树的拖拽","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3105", "parentId":"301", "name":"树其他DOM节点拖拽","url":"../../sample_html/tree/dragdrop-other.html", "target":"frmright","title":"树其他DOM节点拖拽","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3106", "parentId":"301", "name":"树的编辑","url":"../../sample_html/tree/edit.html", "target":"frmright","title":"树的编辑","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3107", "parentId":"301", "name":"右键菜单","url":"../../sample_html/tree/contextmenu.html", "target":"frmright","title":"右键菜单","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3108", "parentId":"301", "name":"自定义外观","url":"../../sample_html/tree/style-custom.html", "target":"frmright","title":"自定义外观","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3109", "parentId":"301", "name":"添加自定义控件","url":"../../sample_html/tree/diy-dom.html", "target":"frmright","title":"添加自定义控件","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3110", "parentId":"301", "name":"节点隐藏","url":"../../sample_html/tree/node-hide.html", "target":"frmright","title":"节点隐藏","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3111", "parentId":"301", "name":"树的分页*","url":"../../sample_html/tree/page.html", "target":"frmright","title":"树的分页","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	


	
	{ "id":"304", "parentId":"3", "name":"综合布局", "isParent": "true","icon": "./skin/index_icon.png","backgroundPosition":"-178px -64px"},

	{ "id":"3401", "parentId":"304", "name":"纵向导航(一级)","url":"../../sample_html/layout/v-single.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3402", "parentId":"304", "name":"纵向导航(一级滚动)","url":"../../sample_html/layout/v-single-scroll.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3403", "parentId":"304", "name":"纵向导航(二级)","url":"../../sample_html/layout/v-double.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3404", "parentId":"304", "name":"横向导航(基本选项卡)","url":"../../sample_html/layout/h-basictab.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},	
	{ "id":"3405", "parentId":"304", "name":"横向导航(流程选项卡)","url":"../../sample_html/layout/h-processtab.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3406", "parentId":"304", "name":"横向导航(滑动)","url":"../../sample_html/layout/h-single-scroll.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3407", "parentId":"304", "name":"横向导航(tab含表格)","url":"../../sample_html/layout/h-basictab-grid.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3408", "parentId":"304", "name":"横向导航(tab含表格2)","url":"../../sample_html/layout/h-basictab-grid2.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3409", "parentId":"304", "name":"纵向+横向导航(动态tab)","url":"../../sample_html/layout/hv-dynamictab.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3410", "parentId":"304", "name":"分隔条布局(左右)","url":"../../sample_html/layout/spliter-h.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3411", "parentId":"304", "name":"分隔条布局(上下)","url":"../../sample_html/layout/spliter-v.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3412", "parentId":"304", "name":"分隔条布局(综合)","url":"../../sample_html/layout/spliter-full.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3413", "parentId":"304", "name":"分隔条布局(弹窗)","url":"../../sample_html/layout/spliter-popup.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3414", "parentId":"304", "name":"部门维护 菜单维护","url":"../../sample_html/layout/nav-management.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3415", "parentId":"304", "name":"用户管理","url":"../../sample_html/layout/user-management.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3419", "parentId":"304", "name":"用户列表","url":"../../sample_html/layout/user-list.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3416", "parentId":"304", "name":"分配资源","url":"../../sample_html/layout/user-assignment.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3417", "parentId":"304", "name":"新窗口打开页面(分离模式)","url":"../../sample_html/split/split-index.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3418", "parentId":"304", "name":"框架右侧嵌入第三方页面","url":"http://www.uileader.com", "target":"frmright","showProgess":false,"icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	

	
	
	{ "id":"4", "parentId":"0", "name":"特效与模板","url":"guide4.html", "isParent": "true","icon": "./skin/index_icon.png","backgroundPosition":"-122px -97px"},

	
	
	

	{ "id":"402", "parentId":"4", "name":"图片特效", "isParent": "true","icon": "./skin/index_icon.png","backgroundPosition":"-16px -96px"},
	{ "id":"4201", "parentId":"402", "name":"图片列表","url":"../../sample_html/pic/list.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-131px 0px"},
	{ "id":"4202", "parentId":"402", "name":"图片标题特效","url":"../../sample_html/pic/title.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-114px 0px"},
	{ "id":"4203", "parentId":"402", "name":"图片预览", "url":"../../sample_html/pic/preview.html","target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-32px -96px"},
	{ "id":"4204", "parentId":"402", "name":"图片部分放大", "url":"../../sample_html/pic/zoom.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-64px -96px"},
	{ "id":"4205", "parentId":"402", "name":"图片滚动", "url":"../../sample_html/pic/scroll.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-80px -96px"},
	{ "id":"4206", "parentId":"402", "name":"图片轮播", "url":"../../sample_html/pic/swiper.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"0px -96px"},
	{ "id":"4207", "parentId":"402", "name":"相册", "url":"../../sample_html/pic/gallery.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"0px -96px"},
	{ "id":"4208", "parentId":"402", "name":"图片瀑布流", "url":"../../sample_html/pic/waterfall.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"0px -96px"},

	
	{ "id":"403", "parentId":"4", "name":"文本特效", "isParent": "true","icon": "./skin/index_icon.png","backgroundPosition":"-98px -96px"},
	{ "id":"4301", "parentId":"403", "name":"文本截取", "url":"../../sample_html/text/slice.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"4302", "parentId":"403", "name":"文章列表", "url":"../../sample_html/text/list.html" ,"target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"4303", "parentId":"403", "name":"文本滚动", "url":"../../sample_html/text/scroll.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	
	{ "id":"404", "parentId":"4", "name":"拖拽特效", "isParent": "true","icon": "./skin/index_icon.png","backgroundPosition":"-80px -32px"},
	{ "id":"4401", "parentId":"404", "name":"拖拽改变尺寸", "url":"../../sample_html/drag/drag-resize.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"0px -112px"},
	{ "id":"4402", "parentId":"404", "name":"拖放与接收", "url":"../../sample_html/drag/drag-drop.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-34px -112px"},
	{ "id":"4403", "parentId":"404", "name":"图标排序", "url":"../../sample_html/drag/drag-sort.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-147px 0px"},
	{ "id":"4404", "parentId":"404", "name":"列表排序", "url":"../../sample_html/drag/drag-sort-list.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-165px 0px"},
	
	{ "id":"405", "parentId":"4", "name":"其他特效", "isParent": "true","icon": "./skin/index_icon.png","backgroundPosition":"-114px -112px"},
	{ "id":"4501", "parentId":"405", "name":"加入收藏","url":"../../sample_html/other/addfav.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-50px -112px"},
	{ "id":"4502", "parentId":"405", "name":"平滑锚点链接", "url":"../../sample_html/other/smoothlink.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-16px -64px"},
	{ "id":"4503", "parentId":"405", "name":"遮罩", "url":"../../sample_html/other/mask.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-66px -112px"},
	{ "id":"4504", "parentId":"405", "name":"进度条", "url":"../../sample_html/other/progressbar.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-98px -112px"},
		
	{ "id":"303", "parentId":"4", "name":"常用模板","icon": "./skin/index_icon.png","backgroundPosition":"-180px 0px"},
	{ "id":"3303", "parentId":"303", "name":"欢迎模板","url":"../../sample_html/templete/welcome.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3304", "parentId":"303", "name":"操作向导模板","url":"../../sample_html/templete/open-process.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3305", "parentId":"303", "name":"操作结果","url":"../../sample_html/templete/result.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3306", "parentId":"303", "name":"404效果","url":"../../sample_html/templete/404.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3307", "parentId":"303", "name":"404效果2","url":"../../sample_html/templete/404-2.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3308", "parentId":"303", "name":"九宫格图标","url":"../../sample_html/templete/icon-grid.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"3309", "parentId":"303", "name":"九宫格图标(拖动)","url":"../../sample_html/templete/icon-grid2.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},



	{ "id":"5", "parentId":"0", "name":"图形化","url":"guide5.html", "isParent": "true","icon": "./skin/index_icon.png","backgroundPosition":"-207px -80px"},
	{ "id":"501", "parentId":"5", "name":"地图","icon": "./skin/index_icon.png","backgroundPosition":"-131px -14px"},
	{ "id":"5101", "parentId":"501", "name":"基础示例","url":"../../sample_html/graphical/map1.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5102", "parentId":"501", "name":"数据控制颜色","url":"../../sample_html/graphical/map2.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5103", "parentId":"501", "name":"外部控制","url":"../../sample_html/graphical/map3.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5104", "parentId":"501", "name":"标记点操作","url":"../../sample_html/graphical/map4.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5105", "parentId":"501", "name":"其他省市地图","url":"../../sample_html/graphical/map5.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},	
	{ "id":"5106", "parentId":"501", "name":"世界地图","url":"../../sample_html/graphical/map6.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5107", "parentId":"501", "name":"切换子地图","url":"../../sample_html/graphical/map7.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	
	{ "id":"502", "parentId":"5", "name":"进度","icon": "./skin/index_icon.png","backgroundPosition":"-173px -97px"},
	{ "id":"5201", "parentId":"502", "name":"进度环1","url":"../../sample_html/graphical/progress-ring.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5202", "parentId":"502", "name":"进度环2","url":"../../sample_html/graphical/progress-ring2.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5203", "parentId":"502", "name":"进度环3","url":"../../sample_html/graphical/progress-ring3.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},

	{ "id":"5204", "parentId":"502", "name":"进度条1","url":"../../sample_html/graphical/progress-rect.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5205", "parentId":"502", "name":"进度条2","url":"../../sample_html/graphical/progress-rect2.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5206", "parentId":"502", "name":"仪表盘","url":"../../sample_html/graphical/dashboard.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},

	{ "id":"503", "parentId":"5", "name":"图表","icon": "./skin/index_icon.png","backgroundPosition":"-190px -95px"},
	{ "id":"5301", "parentId":"503", "name":"柱状图","url":"../../sample_html/graphical/chart-column.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5302", "parentId":"503", "name":"折线图","url":"../../sample_html/graphical/chart-line.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5303", "parentId":"503", "name":"曲线图","url":"../../sample_html/graphical/chart-curve.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5304", "parentId":"503", "name":"曲面图","url":"../../sample_html/graphical/chart-area.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5305", "parentId":"503", "name":"饼状图","url":"../../sample_html/graphical/chart-pie.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5306", "parentId":"503", "name":"环形图","url":"../../sample_html/graphical/chart-ring.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5307", "parentId":"503", "name":"半环图","url":"../../sample_html/graphical/chart-ring-half.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5308", "parentId":"503", "name":"多环图","url":"../../sample_html/graphical/chart-ring-multi.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5309", "parentId":"503", "name":"雷达图","url":"../../sample_html/graphical/chart-radar.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5310", "parentId":"503", "name":"散点图","url":"../../sample_html/graphical/chart-dots.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"504", "parentId":"5", "name":"流程与关系","icon": "./skin/index_icon.png","backgroundPosition":"-207px -96px"},
	{ "id":"5401", "parentId":"504", "name":"时间轴","url":"../../sample_html/graphical/timeline1.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5402", "parentId":"504", "name":"时间轴综合示例","url":"../../sample_html/graphical/timeline2.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5403", "parentId":"504", "name":"鱼骨图","url":"../../sample_html/graphical/fishbone.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5404", "parentId":"504", "name":"关系图","url":"../../sample_html/graphical/relation.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	{ "id":"5405", "parentId":"504", "name":"拓扑图","url":"../../sample_html/graphical/mindmap.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},
	
		
	{ "id":"506", "parentId":"5", "name":"其他","icon": "./skin/index_icon.png","backgroundPosition":"-205px -113px"},
	{ "id":"5601", "parentId":"506", "name":"文档管理","url":"../../sample_html/graphical/computer.html", "target":"frmright","title":"toast","icon": "./skin/index_icon.png","backgroundPosition":"-192px -32px"},

	
	{ "id":"6", "parentId":"0", "name":"资源","url":"guide6.html", "isParent": "true","icon": "./skin/index_icon.png","backgroundPosition":"-139px -97px"},
	
	{ "id":"601", "parentId":"6", "name":"图标库","icon": "./skin/index_icon.png","backgroundPosition":"-1px 0"},
	{ "id":"6101", "parentId":"601", "name":"小图标索引","url":"../../sample_html/icons/icons.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"6102", "parentId":"601", "name":"小图标索引-按钮","url":"../../sample_html/icons/icons-button.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"6105", "parentId":"601", "name":"扁平图标索引","url":"../../sample_html/icons/icons-flat.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"6106", "parentId":"601", "name":"扁平图标组合","url":"../../sample_html/icons/icons-group.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"6103", "parentId":"601", "name":"fontawsome使用","url":"../../sample_html/icons/icons-awesome-use.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"},
	{ "id":"6104", "parentId":"601", "name":"fontawsome索引","url":"../../sample_html/icons/icons-awesome-index.html", "target":"frmright","icon": "./skin/index_icon.png","backgroundPosition":"-191px -32px"}
	
	
];

var setting = {
	data: {
		simpleData: {
			idKey: "id",
			pIdKey: "parentId",
			enable: true
		},
		key: {
			children: "children"
		}
	}
};
var	show_on=0;
function transition(setting, sNodes) {
	var i, l,
		key = setting.data.simpleData.idKey,
		parentKey = setting.data.simpleData.pIdKey,
		childKey = setting.data.key.children;
	if(!key || key == "" || !sNodes) return [];
	var r = [];
	var tmpMap = {};
	for(i = 0, l = sNodes.length; i < l; i++) {
		tmpMap[sNodes[i][key]] = sNodes[i];
	};
	for(i = 0, l = sNodes.length; i < l; i++) {
		if(tmpMap[sNodes[i][parentKey]] && sNodes[i][key] != sNodes[i][parentKey]) {
			if(!tmpMap[sNodes[i][parentKey]][childKey])
				tmpMap[sNodes[i][parentKey]][childKey] = [];
			tmpMap[sNodes[i][parentKey]][childKey].push(sNodes[i]);
		} else {
			r.push(sNodes[i]);
		};
	};
	return r;
};

function switchMenu(switch_on){
	if(!switch_on){
		$("#bs_left").stop().animate({
			width:"42px"
		},200);
		$(".menu_content").find(".menu_content_content").stop().slideUp(50);
		$("#bs_left").removeClass("lbox_middlecenter_content");
		$(".bs_left_shrink i").removeClass("active");
		show_on=1;
	}else{
		$("#bs_left").stop().animate({
			width:"220px"
		},200);
		$(".menu_content").find(".menu_content_content").stop().show();
		$("#bs_left").addClass("lbox_middlecenter_content");
		$(".bs_left_shrink i").addClass("active");
		show_on=0;
	};
}
function switchHead(state){
	if(!state){
		$("#hbox").hide();
		$("#hbox").height(0);
		autoReset();
	}
	else{
		$("#hbox").hide();
		$("#hbox").height(oldBannerHeight);
		autoReset();
	}
}
$(function(){	
	var content = transition(setting, sNodes);
	$(".hbox_content_right_menu").empty();
	var html='';
	for(var i=0;i<content.length;i++){
		if(content[i].parentId=="0"){
			$(".hbox_content_right_menu").append('<li url="'+content[i].url+'"><i style="background-image:url('+content[i].icon+');background-position:'+content[i].backgroundPosition+'"></i>'+content[i].name+'</li>');
		};
		html+='<div class="menu_content">';
		if(content[i].children!=undefined){
			for(var j=0;j<content[i].children.length;j++){
				if(content[i].children[j].children!=undefined){
					html+='<div class="menu_content_win">';
					html+='<div class="menu_content_title clearfloat"><i style="background-image:url('+content[i].children[j].icon+');background-position:'+content[i].children[j].backgroundPosition+'"></i><span>'+content[i].children[j].name+'</span></div>';
					html+='<div class="menu_content_content">';
					for(var k=0;k<content[i].children[j].children.length;k++){
						html+='<a onclick="showProgressBar(\'加载中...\')"  href="'+content[i].children[j].children[k].url+'" target="'+content[i].children[j].children[k].target+'" class="menu_content_list clearfloat "><i style="background-image:url('+content[i].children[j].children[k].icon+');background-position:'+content[i].children[j].children[k].backgroundPosition+'"></i>'+content[i].children[j].children[k].name+'</a>';
					};
					html+='</div>';
					html+='</div>';
				}else{
					html+='<a onclick="showProgressBar(\'加载中...\')"  href="'+content[i].children[j].url+'" target="'+content[i].children[j].target+'" class="menu_content_list clearfloat "><i></i>'+content[i].children[j].name+'</a>';
				};
			};
		}
		html+='</div>';
	};
	$(".lbox_middlecenter_content").append(html);
	//右侧头部js
	$(".right_toggle").hover(function() {
		$(this).find(".right_toggle_content").stop().slideToggle(200);
	});
	$(".menu_content_list").click(function(){
		if($(this).hasClass()!="active"){
			$(this).parents(".lbox_middlecenter_content").find(".menu_content_list").removeClass("active");
			$(this).addClass("active");
		};
		$(".rbox_topcenter span").text($(this).parent().siblings(".menu_content_title").find("span").text()+' / '+$(this).text());
	});
	//组件导航切换
	$(".hbox_content_right_menu li").click(function(){
		var index=$(this).index();
		$("#bs_left .menu_content").eq(index).show().siblings(".menu_content").hide();
		if($(this).hasClass()!="active"){
			$(this).addClass("active").siblings("li").removeClass("active");
		};
		$("#bs_left").stop().animate({scrollTop:0},500);
		$("#bs_right iframe").attr("src",$(this).attr("url"));
		$(".rbox_topcenter span").text('');
	});
	//左侧导航收缩
	$(".bs_left_shrink i").click(function(){
		if($(this).hasClass("active")){
			switchMenu(0);
		}else{
			switchMenu(1);
		};
	});
	$(".menu_content_win").hover(function(){
		if(show_on!=0){
			$(this).find(".menu_content_content").addClass("active").stop().show();
			$(this).find(".menu_content_title").addClass("hover");
			var top = $(this).find(".menu_content_content").offset().top; //子集距离浏览器顶部的距离
			var all_height = $(window).height(); //可视窗口的高度
			var self_height = $(this).find(".menu_content_content").height(); //子集的高度
			var end_hei = all_height - top - self_height; //子集距离浏览器底部的距离
			if(end_hei < 0) {
				$(this).find(".menu_content_content").stop().animate({
					"top": -(top-130)
				})
			};
		};
	},function(){
		if(show_on!=0){
			$(this).find(".menu_content_content").removeClass("active").stop().hide();
			$(this).find(".menu_content_title").removeClass("hover");
			$(this).find(".menu_content_content").stop().animate({
				"top": 0
			})
		}
	});
	//按钮控制导航收缩
	$(".right_toggle_fullscreen").click(function(){
		var iconBtn=$(this);
		if(iconBtn.hasClass('right_toggle_screen')){
            switchMenu(1);
            fullScrennHander(false);
            iconBtn.removeClass('right_toggle_screen');
            $(this).find("div").text("全屏");
        }
        else{
          top.switchMenu(0);
          if (typeof window.screenX === "number"){
            top.fullScrennHander(true);
            }
          else{
            top.Toast('showNoticeToast', '您的浏览器不支持全屏，如果需要，请手动按F11键。');
          }
          iconBtn.addClass('right_toggle_screen');
          $(this).find("div").text("还原");
        }
	});
	
	
	//默认第一个组件内容显示
	//$(".menu_content").eq(0).show().find("a").eq(0).addClass("active");
	//$("#bs_right iframe").attr("src",$(".menu_content").eq(0).find("a").eq(0).attr("href"));
	$(".hbox_content_right_menu li").eq(0).addClass("active");
	$(".menu_content").eq(0).show()
})
