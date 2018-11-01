/**
			 * 根据圆心、半径、角度得到元素的坐标
			 * @return {[type]} [点的坐标]
			 */

			function getLocationByDeg(deg, percent, isOutter) {
				var x0 = 160,
					y0 = 160;
				var r = !!percent ? 83 * percent : 93;
				r = percent === 0 ? 3 : r;
				r = !isOutter ? r : 125;
				var x1 = parseInt((x0 + r * Math.cos(deg * 3.14 / 180)).toFixed(0));
				var y1 = parseInt((x0 + r * Math.sin(deg * 3.14 / 180)).toFixed(0));
				return { 'x': x1, 'y': y1 };
			}

			/**
			 * 获得所有需要的点的位置
			 * @param {[type]} initParams [description]
			 * @return {[type]} [description]
			 */
			function getDotsPosition(initParams) {
				//所有外面标记点的坐标集合
				var outsideDots = [];
				var outsideTextDots = [];
				var insideDots = [];
				var outLineDots = [];
				var totalOutLineObj = {
					'100': [],
					'75': [],
					'50': [],
					'25': []
				};

				var dotNums = initParams.length;
				var deg = 360 / dotNums; //每个扇形所占的角度
				for(var i = 0; i < dotNums; i++) {
					outsideDots.push(getLocationByDeg(270 - deg * i));
					outsideTextDots.push(getLocationByDeg(270 - deg * i, 1, true));
					insideDots.push(getLocationByDeg((270 - deg * i), (initParams[i].score) / 100));
					outLineDots.push(getLocationByDeg(270 - deg * i, 1));
					totalOutLineObj['100'].push(getLocationByDeg((270 - deg * i), 1));
					totalOutLineObj['75'].push(getLocationByDeg((270 - deg * i), 0.75));
					totalOutLineObj['50'].push(getLocationByDeg((270 - deg * i), 0.5));
					totalOutLineObj['25'].push(getLocationByDeg((270 - deg * i), 0.25));
				}

				return { 'outsideDots': outsideDots, 'outsideTextDots': outsideTextDots, 'insideDots': insideDots, 'outLineDots': outLineDots, 'totalOutLineObj': totalOutLineObj };
			}

			//将内部的点连接起来并填充颜色
			function drawPath(dots) {
				var length = dots.length;
				var p = ['M'];

				for(var i = 0; i < length; i++) {
					var dot = dots[i];
					p.push(dot.x, dot.y, 'L');
				}
				p = p.slice(0, -1);
				p.push('Z');
				return p;
			}

			function drawRadarChart(initParams) {
				var paramsLength = initParams.length;
				var colors = [
					'rgb(92, 215, 120)',
					'rgb(120, 164, 255)',
					'rgb(200, 150, 254)',
					'rgb(255, 130, 121)',
					'rgb(254, 178, 50)',
					'rgb(177, 221, 48)'
				];

				for(var i = 0; i < paramsLength; i++) {
					initParams[i]['color'] = colors[i % 5];
				}

				var dotLength = initParams.length;
				var dotsPosition = getDotsPosition(initParams);
				var outsideDots = dotsPosition.outsideDots,
					outsideTextDots = dotsPosition.outsideTextDots,
					insideDots = dotsPosition.insideDots,
					outLineDots = dotsPosition.outLineDots,
					totalOutLineObj = dotsPosition.totalOutLineObj;

				var paper = Raphael(document.getElementById("radar-chart-wrap"), 320, 320);
				paper.setViewBox(0, 0, 320, 320); 
				var st = paper.set();

				//画最外层的折线(100%,75%,50%,25)
				paper.path().attr({
					'path': drawPath(totalOutLineObj['100']),
					'fill': 'rgb(148, 255, 139)',
					'stroke': 'rgb(205, 241, 205)',
					'fill-opacity': 0.12
				});

				paper.path().attr({
					'path': drawPath(totalOutLineObj['75']),
					'fill': 'rgb(148, 255, 139)',
					'stroke': 'rgb(205, 241, 205)',
					'fill-opacity': 0.12
				});

				paper.path().attr({
					'path': drawPath(totalOutLineObj['50']),
					'fill': 'rgb(148, 255, 139)',
					'stroke': 'rgb(205, 241, 205)',
					'fill-opacity': 0.12
				});

				paper.path().attr({
					'path': drawPath(totalOutLineObj['25']),
					'fill': 'rgb(148, 255, 139)',
					'stroke': 'rgb(205, 241, 205)',
					'fill-opacity': 0.12
				});

				for(var i = 0; i < dotLength; i++) {
					//画外部的点线文字
					var outsideDot = outsideDots[i];
					var outsideTextDot = outsideTextDots[i];
					var nameY = outsideTextDot.y,
						nameX = outsideTextDot.x,
						scoreY = outsideTextDot.y,
						scoreX = outsideTextDot.x;
					if(nameY < 160) {
						nameY += 20;
					} else if(nameY > 160) {
						scoreY -= 10;
						nameY += 10;
					} else if(nameY == 160) {
						scoreY -= 10;
						nameY += 10;
					}
					st.push(
						paper.path('M' + outLineDots[i].x + ',' + outLineDots[i].y + 'L160,160Z').attr({
							// 'fill': '#eee',
							'stroke': 'rgb(187, 223, 187)'
						}),
						paper.circle(outsideDot.x, outsideDot.y, 3).attr({
							'fill': initParams[i].color,
							'stroke': initParams[i].color
						}),
						paper.text(nameX, nameY, initParams[i].name).attr({
							'font-size': '12px',
							'fill': 'rgb(102, 102, 102)'
						}),
						paper.text(scoreX, scoreY, initParams[i].score).attr({
							'fill': initParams[i].color,
							'font-size': '18px'
						})
					);
				}
				paper.path().attr({
					'path': drawPath(insideDots),
					//'fill': '270-rgba(159,240,79,0.4)-rgba(56,189,88,0.4)',
					'stroke': 'rgb(91, 208, 48)',
					'fill': "rgb(91, 208, 48)",
            		'fill-opacity': 0.6
				});
			}

			$(function(){
				drawRadarChart([{
					'name': '阅读',
					'score': 15
				}, {
					'name': '听力',
					'score': 80
				}, {
					'name': '书写',
					'score': 60
				}, {
					'name': '翻译',
					'score': 86
				}, {
					'name': '口语',
					'score': 50
				}
				, {
					'name': '单词',
					'score': 10
				}

			]);
			})

			