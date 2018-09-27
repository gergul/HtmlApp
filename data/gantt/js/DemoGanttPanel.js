TaskPriority = {
	Low : 0,
	Normal : 1,
	High : 2
};

/* 导入Project的弹出窗口 */
Ext
		.define(
				'MSProjectImportPanel',
				{
					// extend : 'Ext.form.Panel',
					extend : 'Ext.window.Window',
					width : 300,
					frame : true,
					title : '导入Project文件',
					bodyPadding : '10 10 0',
					layout : "fit",
					defaults : {
						anchor : '100%',
						allowBlank : false,
						msgTarget : 'side',
						labelWidth : 50
					},
					initComponent : function() {
						this.addEvents('dataavailable');
						var w = this;
						/*
						 * 有一个非常奇怪的错误会导致以下的【导入Project】窗口运行错误。 当新建了一个项目的时候，数据集为空。
						 * 这时候浏览器会报parentNode的错误。 这时候你要是点击【导入Project】， 窗口不能展示
						 */
						Ext
								.apply(
										this,
										{
											items : [ new Ext.form.Panel(
													{
														title : "表单",
														height : 120,
														width : 200,
														frame : true,
														collapsible : true,
														layout : "fit",
														items : [ {
															xtype : 'filefield',
															id : 'form-file',
															emptyText : '上传 .mpp 文件',
															fieldLabel : '选择文件',
															name : 'file',
															buttonText : '选择文件',
															buttonConfig : {
																iconCls : 'upload-icon'
															}
														} ],
														buttons : [
																{
																	text : '上传',
																	handler : function() {
																		var panel = this
																				.up('form');
																		var form = panel
																				.getForm();
																		if (form
																				.isValid()) {
																			form
																					.submit( {
																						url : APIVAR.url.upload
																								+ '&pid='
																								+ pid,
																						waitMsg : '正在加载数据...',
																						failure : function(
																								form,
																								action) {
																							msg(
																									'上传出错',
																									'请确认上传文件格式是否正确. 错误位置: ' + action.result.msg);
																						},
																						success : function(
																								form,
																								action) {
																							// w.fireEvent('dataavailable',
																							// panel,
																							// action.result.data);
																							location
																									.reload();
																						}
																					});
																		}
																	}
																},
																{
																	text : '重置',
																	handler : function() {
																		this
																				.up(
																						'form')
																				.getForm()
																				.reset();
																	}
																} ]
													}) ]

										});

						this.callParent(arguments);
					}
				});

var msg = function(title, msg) {
	Ext.Msg.show( {
		title : title,
		msg : msg,
		minWidth : 200,
		modal : true,
		icon : Ext.Msg.INFO,
		buttons : Ext.Msg.OK
	});
};

Ext
		.define(
				"MyApp.DemoGanttPanel",
				{
					extend : "Gnt.panel.Gantt",
					requires : [ 'Gnt.plugin.TaskContextMenu',
							'Gnt.column.StartDate', 'Gnt.column.EndDate',
							'Gnt.column.Duration', 'Gnt.column.PercentDone',
							'Gnt.column.ResourceAssignment',
							'Sch.plugin.TreeCellEditing', 'Sch.plugin.Pan' ],
					rightLabelField : 'Responsible',
					highlightWeekends : true,
					showTodayLine : true,
					loadMask : true,
					enableProgressBarResize : true,

					initComponent : function() {

						Ext
								.apply(
										this,
										{
											enableBaseline : true,
											baselineVisible : false,
											lockedGridConfig : {
												width : 300,
												title : '任务列表',
												collapsible : true
											},

											// Experimental
											schedulerConfig : {
												collapsible : true,
												title : '甘特图'
											},

											leftLabelField : {
												dataIndex : 'Name',
												editor : {
													xtype : 'textfield'
												}
											},

											// Define an HTML template for the
											// tooltip
											tooltipTpl : new Ext.XTemplate(
													'<h4 class="tipHeader">{Name}</h4>',
													'<table class="taskTip">',
													'<tr><td>开始:</td> <td align="right">{[Ext.Date.format(values.StartDate, "y-m-d")]}</td></tr>',
													'<tr><td>结束:</td> <td align="right">{[Ext.Date.format(Ext.Date.add(values.EndDate, Ext.Date.MILLI, -1), "y-m-d")]}</td></tr>',
													'<tr><td>进度:</td><td align="right">{PercentDone}%</td></tr>',
													'</table>').compile(),

											eventRenderer : function(task) {
												return {
													style : 'background-color: #' + task.data.TaskColor
												};
											},

											// Define the static columns
											columns : [
													// column displaying task
													// color
													{
														header : 'Color',
														xtype : 'templatecolumn',
														header : "标记",
														width : 50,
														tdCls : 'sch-column-color',
														// locked: true,
														field : {
															allowBlank : false
														},
														tpl : '<div class="color-column-inner" style="background-color:#{TaskColor}">&nbsp;</div>',
														listeners : {
															click : function(
																	panel, el,
																	a, b,
																	event,
																	record) {
																event
																		.stopEvent();
																this.rec = record;
																this
																		.showColumnMenu(
																				el,
																				event,
																				record);
															}
														},
														showColumnMenu : function(
																el, event, rec) {
															// if color menu is
															// not present,
															// create a new
															// Ext.menu.Menu
															// instance
															if (!this.colorMenu) {
																this.colorMenu = new Ext.menu.Menu(
																		{
																			cls : 'gnt-locked-colormenu',
																			plain : true,
																			items : [ {
																				text : '修改任务颜色',
																				menu : {
																					showSeparator : false,
																					items : [ Ext
																							.create(
																									'Ext.ColorPalette',
																									{
																										listeners : {
																											select : function(
																													cp,
																													color) {
																												this.tpl
																														.apply( {
																															TaskColor : color
																														});
																												// 'TaskColor'必须在model里面定义好
																												this.rec
																														.set(
																																'TaskColor',
																																color);
																											},
																											scope : this
																										}
																									}) ]
																				}
																			} ]
																		});
															}

															this.colorMenu
																	.showAt(event.xy);
														}
													},
													// wbs列有问题
													new Gnt.column.WBS(),

													{
														xtype : 'treecolumn',
														header : '任务名称',
														sortable : true,
														dataIndex : 'Name',
														width : 200,
														// locked: true,
														field : {
															allowBlank : false
														},
														renderer : function(v,
																meta, r) {
															if (!r.data.leaf)
																meta.tdCls = 'sch-gantt-parent-cell';

															return v;
														}
													},
													/*
													 * { xtype :
													 * 'startdatecolumn',
													 * header: '开始时间' },
													 */
													new Gnt.column.StartDate( {
														// xtype:
														// 'startdatecolumn',
															header : '开始时间'
														}),
													/*
													 * { xtype :
													 * 'enddatecolumn', hidden :
													 * true, header: '结束时间' },
													 */
													new Gnt.column.EndDate( {
														// xtype:
														// 'startdatecolumn',
															header : '结束时间'

														}),
													{
														xtype : 'durationcolumn',
														header : '工期'
													},
													{
														xtype : 'percentdonecolumn',
														width : 50,
														header : '完成率'
													},

													// 前置任务， 工期， 部门，负责人，资源
													{

														width : 50,
														header : '前置任务',
														xtype : 'predecessorcolumn'
													},

													{

														width : 50,
														header : '后继任务',
														xtype : 'successorcolumn'
													},

													{

														width : 50,
														header : '部门'

													},

													{

														width : 50,
														header : '负责人'

													},

													{
														header : '优先级',
														width : 50,
														dataIndex : 'Priority',
														renderer : function(v,
																m, r) {
															switch (v) {
															case TaskPriority.Low:
																return 'Low';

															case TaskPriority.Normal:
																return 'Normal';

															case TaskPriority.High:
																return 'High';
															}
														}
													},
													{
														xtype : 'booleancolumn',
														width : 50,

														header : '人工',

														dataIndex : 'ManuallyScheduled',

														field : {
															xtype : 'combo',
															store : [ 'true',
																	'false' ]
														}
													},

													{
														// xtype : 'text',
														width : 50,
														header : '自定义的列',
														renderer : function() {
															return '自定义的列';
														}
													}

											],

											// Define the buttons that are
											// available for user interaction
											tbar : this.createToolbar()

										});

						this.callParent(arguments);
					},

					createToolbar : function() {
						return [
								{
									xtype : 'buttongroup',
									title : '视图',
									columns : 3,
									items : [ {
										iconCls : 'icon-prev',
										text : '后退',
										scope : this,
										handler : function() {
											this.shiftPrevious();
										}
									}, {
										iconCls : 'icon-next',
										text : '前进',
										scope : this,
										handler : function() {
											this.shiftNext();
										}
									}, {
										text : '折叠所有',
										iconCls : 'icon-collapseall',
										scope : this,
										handler : function() {
											this.collapseAll();
										}
									}, {
										text : '全屏',
										iconCls : 'icon-fullscreen',
										disabled : !this._fullScreenFn,
										handler : function() {
											this.showFullScreen();
										},
										scope : this
									}, {
										text : '合适屏幕',
										iconCls : 'zoomfit',
										handler : function() {
											this.zoomToFit();
										},
										scope : this
									}, {
										text : '展开所有',
										iconCls : 'icon-expandall',
										scope : this,
										handler : function() {
											this.expandAll();
										}
									} ]
								},
								{
									xtype : 'buttongroup',
									title : '缩放',
									columns : 2,
									items : [
											{
												text : '6 周',
												scope : this,
												handler : function() {
													var sp = this.taskStore
															.getTotalTimeSpan();
													this.switchViewPreset(
															'weekAndMonth',
															sp.start, sp.end);
												}
											},
											{
												text : '10 周',
												scope : this,
												handler : function() {
													var sp = this.taskStore
															.getTotalTimeSpan();
													this.switchViewPreset(
															'weekAndDayLetter',
															sp.start, sp.end);
												}
											},
											{
												text : '1 一年',
												scope : this,
												handler : function() {
													var sp = this.taskStore
															.getTotalTimeSpan();
													this.switchViewPreset(
															'monthAndYear',
															sp.start, sp.end);
												}
											},
											{
												text : '5 年',
												scope : this,
												handler : function() {
													var sp = this.taskStore
															.getTotalTimeSpan();

													this.switchViewPreset(
															'monthAndYear',
															sp.start, sp.end);
												}
											} ]
								},
								// 编辑功能
								{
									xtype : 'buttongroup',
									title : '编辑',
									columns : 3,
									items : [
											{
												text : '添加任务',
												// iconCls: 'icon-add',
												scope : this,
												handler : function() {
													var original = this
															.getSelectionModel().selected.items[0];
													var model = this
															.getTaskStore().model;

													var newTask = new model( {
														leaf : true
													});

													newTask.setPercentDone(0);
													newTask.setName("新任务...");
													// newTask.setStartDate((original
													// &&
													// original.getStartDate())
													// || null);
													// /newTask.setEndDate((original
													// && original.getEndDate())
													// || null);
													// newTask.setDuration((original
													// &&
													// original.getDuration())
													// || null);
													// newTask.setDurationUnit((original
													// &&
													// original.getDurationUnit())
													// || 'd');

													newTask
															.set(
																	newTask.startDateField,
																	(original && original
																			.getStartDate())
																			|| null);
													newTask
															.set(
																	newTask.endDateField,
																	(original && original
																			.getEndDate())
																			|| null);
													newTask
															.set(
																	newTask.durationField,
																	(original && original
																			.getDuration())
																			|| null);
													newTask
															.set(
																	newTask.durationUnitField,
																	(original && original
																			.getDurationUnit()) || 'd');

													if (original) {
														original
																.addTaskBelow(newTask);
													} else {
														this.taskStore
																.getRootNode()
																.appendChild(
																		newTask);
													}
												}

											},
											{
												enableToggle : true,
												id : 'demo-readonlybutton',
												scope : this,
												text : '只读模式',
												pressed : false,
												handler : function() {
													this
															.setReadOnly(Ext
																	.getCmp("demo-readonlybutton").pressed);
												}
											},

											{
												text : '任务降级',
												// iconCls : 'indent',
												scope : this,
												handler : function() {
													var sm = this.lockedGrid
															.getSelectionModel();
													this.taskStore.indent(sm
															.getSelection());
												}
											},
											{
												text : '任务升级',
												// iconCls : 'outdent',
												scope : this,
												handler : function() {
													var sm = this.lockedGrid
															.getSelectionModel();
													this.taskStore.outdent(sm
															.getSelection());
												}
											},
											{
												text : '保存修改',
												iconCls : 'icon-save',
												scope : this,
												handler : function() {
													this.taskStore
															.sync( {
																success : function() {

																	Ext.MessageBox
																			.alert(
																					"恭喜",
																					"数据保存成功！");
																},
																failure : function() {

																	Ext.MessageBox
																			.alert(
																					"错误",
																					"数据保存错误");
																}

															});
												}
											}

									]
								},

								{
									xtype : 'buttongroup',
									title : '日程',
									columns : 5,
									defaults : {
										scale : "large"
									},
									items : [ {
										text : '0%',
										scope : this,
										handler : function() {
											this.applyPercentDone(0);
										}
									}, {
										text : '25%',
										scope : this,
										handler : function() {
											this.applyPercentDone(25);
										}
									}, {
										text : '50%',
										scope : this,
										handler : function() {
											this.applyPercentDone(50);
										}
									}, {
										text : '75%',
										scope : this,
										handler : function() {
											this.applyPercentDone(75);
										}
									}, {
										text : '100%',
										scope : this,
										handler : function() {
											this.applyPercentDone(100);
										}
									} ]
								},
								{
									xtype : 'buttongroup',
									title : '面板',
									columns : 3,
									defaults : {
										scale : "large"
									},
									items : [
											{
												text : '日历面板',
												scope : this,
												handler : function() {
													var conf = {
														calendar : this.taskStore.calendar
													};

													var editorWindow = new Gnt.widget.calendar.CalendarWindow(
															conf);
													editorWindow.show();
												}
											},
											{
												text : '任务面板',
												scope : this,
												handler : function() {
													var st = this
															.getView()
															.getSelectionModel()
															.getSelection();
													if (st.length > 0) {

														this.taskEditor
																.showTask(st[0]);

													} else {
														Ext.Msg.alert('提示',
																'请选择一个任务');
													}
												}
											},
											{
												text : '导入Project',
												scope : this,
												handler : function() {
													var g = this;
													var window = new MSProjectImportPanel(
															{
																listeners : {
																	dataavailable : function(
																			form,
																			data) {
																		// msg('Success',
																		// 'Data
																		// from
																		// .mpp
																		// file
																		// loaded
																		// ');

																		g.taskStore
																				.setRootNode(data.tasks);
																		g.resourceStore
																				.loadData(data.resources);
																		g.assignmentStore
																				.loadData(data.assignments);
																		g.dependencyStore
																				.loadData(data.dependencies);

																		var column, xtype;

																		for ( var i = 0, l = data.columns.length; i < l; i++) {

																			xtype = data.columns[i].xtype;
																			delete data.columns[i].xtype;

																			column = Ext
																					.widget(
																							xtype,
																							data.columns[i]);

																			g.lockedGrid.headerCt
																					.add(column);
																		}
																		g.lockedGrid.headerCt
																				.remove(0);
																		g.lockedGrid
																				.getView()
																				.refresh();

																		g
																				.expandAll();

																		var span = g.taskStore
																				.getTotalTimeSpan();
																		if (span.start
																				&& span.end) {
																			g
																					.setTimeSpan(
																							span.start,
																							span.end);
																		}
																	}
																}
															});
													window.show();
												}
											} ]
								},

								'->',
								{
									xtype : 'buttongroup',
									title : '可扩展功能',
									columns : 4,
									items : [
											{
												text : '关键路径高亮显示',
												iconCls : 'togglebutton',
												scope : this,
												enableToggle : true,
												handler : function(btn) {
													var v = this
															.getSchedulingView();
													if (btn.pressed) {
														v
																.highlightCriticalPaths(true);
													} else {
														v
																.unhighlightCriticalPaths(true);
													}
												}
											},
											{
												iconCls : 'action',
												text : '高亮显示7天以上的任务',
												scope : this,
												handler : function(btn) {
													/*this.taskStore
															.getRootNode()
															.cascadeBy(
																	function(
																			task) {
																		if (Sch.util.Date
																				.getDurationInDays(
																						task
																								.get('StartDate'),
																						task
																								.get('EndDate')) > 7) {
																			var el = this
																					.getSchedulingView()
																					.getElementFromEventRecord(
																							task);
																			el
																					&& el
																							.frame('lime');
																		}
																	}, this);*/
													this.taskStore.queryBy(function (task) {
				                                        if (task.data.leaf && task.getDuration() > 7) {
				                                            var el = this.getSchedulingView().getElementFromEventRecord(task);
				                                            el && el.frame('lime');
				                                        }
				                                    }, this);
												}
											},
											{
												iconCls : 'togglebutton',
												text : '显示: 进度小于30%的任务',
												scope : this,
												enableToggle : true,
												toggleGroup : 'filter',
												handler : function(btn) {
													if (btn.pressed) {
														this.taskStore.filterTreeBy(function (task) {
					                                        return task.get('PercentDone') < 30;
					                                    });
													} else {
														this.taskStore.clearTreeFilter();
													}
												}
											},
											{
												iconCls : 'togglebutton',
												text : '前置任务影响',
												scope : this,
												enableToggle : true,
												handler : function(btn) {
													this
															.setCascadeChanges(btn.pressed);
													if(btn.pressed){
														alert("勾选本选项后， 前置任务改动后， 相关的后继任务会自动排程。");
														
													}
													
												}
											},
											{
												iconCls : 'action',
												text : '滚动到最后一个任务',
												scope : this,

												handler : function(btn) {
													var latestEndDate = new Date(0),
				                                    latest;
													this.taskStore.getRootNode().cascadeBy(function (task) {
				                                        if (task.get('EndDate') >= latestEndDate) {
				                                            latestEndDate = task.get('EndDate');
				                                            latest = task;
				                                        }
				                                    });
													this.getSchedulingView().scrollEventIntoView(latest, true);
												}
											},
											{
												xtype : 'textfield',
												emptyText : '按关键字查找',
												scope : this,
												width : 150,
												enableKeyEvents : true,
												listeners : {
											        keyup      : {
											            fn     : function (field, e) {
											                var value = field.getValue();
											                var regexp = new RegExp(Ext.String.escapeRegex(value), 'i')

											                if (value) {
											                    this.taskStore.filterTreeBy(function (task) {
											                        return regexp.test(task.get('Name'))
											                    });
											                } else {
											                    this.taskStore.clearTreeFilter();
											                }
											            },
											            buffer : 200,
											            scope:this
											        },
											        specialkey : {
											            fn : function (field, e) {
											                if (e.getKey() === e.ESC) {
											                    field.reset();

											                    this.taskStore.clearTreeFilter();
											                }
											            },
											            scope:this
											        }
											    }
											},
											{
												text : '查看计划',
												enableToggle : true,
												pressed : false,
												scope : this,
												handler : function() {
													this.el
															.toggleCls('sch-ganttpanel-showbaseline');
												}
											}

									]
								} ];
					},

					applyPercentDone : function(value) {
						this.getSelectionModel().selected.each(function(task) {
							task.setPercentDone(value);
						});
					},

					showFullScreen : function() {
						this.el.down('.x-panel-body').dom[this._fullScreenFn]();
					},

					// Experimental, not X-browser
					_fullScreenFn : (function() {
						var docElm = document.documentElement;

						if (docElm.requestFullscreen) {
							return "requestFullscreen";
						} else if (docElm.mozRequestFullScreen) {
							return "mozRequestFullScreen";
						} else if (docElm.webkitRequestFullScreen) {
							return "webkitRequestFullScreen";
						}
					})()
				});