(function(I,g,p){I.Ya=I.Ya||{};I.ya_hit_param=I.ya_hit_param||[];var s=Math.round(Math.random()*(1<<31-1)),v,z,n,u=I.location,H=I.navigator,t=u.protocol=="https:"?"https:":"http:",x="$Rev: 1304 $".match(/(\d+)/)[1];var A;function B(c){return H.userAgent.toLowerCase().indexOf(c)!=-1}var a=B("opera"),f=B("applewebkit/"),e=B("gecko/"),m=!a&&B("msie");var y=64,j=m?512:2048,C=m?512:2048,J=m?100:400,d=50,E=100,l=15000,r=new RegExp("\\.(7z|aac|ai|avi|apk|bmp|cab|csv|cdr|dmg|djvu?|doc(x|m|b)?|eps|exe|flv|gif|gz|jpe?g|js|m4a|mp(3|4|e?g)|mov|msi|ods|pdf|phps|png|ppt(x|m|b)?|psd|rar|rss|rtf|sea|sit|tar|tif?f|torrent|txt|wav|wma|wmv|xls(x|m|b)?|xpi|zip)$","i"),h=new Date().getTime();I.Ya.Metrika=function(aq,ab,aG,O){var az=this,ak="",aI=null;if(!I.Ya._yaCounter){I.Ya._yaCounter=az}var ap=null;if(typeof aq=="object"){ap=aq;O=aq.defer;ak=aq.ut;aG=aq.type;ab=aq.params;aq=aq.id}aq=aq||0;aG=aG||0;var aF="//mc.yandex.ru/watch/",ad="//mc.yandex.ru/clmap/";var Q=[];function W(aO,aQ,aP){var aR=aP;Q[Q.length]=[aP,aR];if(aO.addEventListener){aO.addEventListener(aQ,aR,false)}else{if(aO.attachEvent){aO.attachEvent("on"+aQ,aR)}}}function P(aP,aR,aQ){for(var aO=0;aO<Q.length;aO++){if(Q[aO]&&Q[aO][0]==aQ){var aS=Q[aO][1];delete Q[aO];break}}if(aS){if(aP.removeEventListener){aP.removeEventListener(aR,aS,false)}else{if(aP.detachEvent){aP.detachEvent("on"+aR,aS)}}}}function aN(aP){return 0;var aQ=g.links,aS,aT=0;for(var aR=0,aO=aQ.length;aR<aO;aR++){aS=aQ[aR];if(aS===aP){return aP}if(aS.href==aP.href){aT++}}return aT}function ac(aP,aO){aO=aO||256;if(!aP){return""}if(aP.length>aO){aP=aP.substr(0,aO)}return(I.encodeURIComponent||I.escape)(aP).replace(/\+/g,"%2B")}function i(aQ){function aT(aU){return aU?aU.replace(/\\/,"\\\\").replace(/"/,'\\"'):""}switch(aQ.constructor){case Boolean:return aQ.toString();case Number:return isFinite(aQ)?aQ.toString():"null";case String:return'"'+aT(aQ)+'"';case Array:var aO=[];for(var aR=0,aS=aQ.length;aR<aS;aR++){aO[aO.length]=i(aQ[aR])}return"["+aO.join(",")+"]";case Object:var aO="{",aR=0;for(var aP in aQ){if(!aQ.hasOwnProperty(aP)){continue}aO+=(aR?",":"")+'"'+aT(aP)+'":'+i(aQ[aP]);aR++}aO+="}";return aO;default:return"null"}}function ay(){return Math.floor(Math.random()*1000000)}function aE(){return +new Date()}function an(aQ){var aR=aE();for(var aP=1;aP>0;aP++){if(aP%1000==0){var aO=aE();if(aR>aO){break}if(aO-aR>aQ){break}}}}function ah(aO){return aO?aO.toString().replace(/<\/?[^>]+>/gi,""):""}function R(aO){return aO?aO.toString().replace(/^\s+/,"").replace(/\s+$/,""):""}function U(aO){return R(ah(aO.innerHTML))}function au(aO){return aO.replace(/\^/g,"\\^").replace(/\$/g,"\\$").replace(/\./g,"\\.").replace(/\[/g,"\\[").replace(/\]/g,"\\]").replace(/\|/g,"\\|").replace(/\(/g,"\\(").replace(/\)/g,"\\)").replace(/\?/g,"\\?").replace(/\*/g,"\\*").replace(/\+/g,"\\+").replace(/\{/g,"\\{").replace(/\}/g,"\\}")}function aM(aO){return aO?aO.split(/\?/)[0]:""}function ao(aO,aQ){if(!aO||!aQ){return false}var aS=[];for(var aP=0;aP<aQ.length;aP++){aS.push(au(aQ[aP]))}var aR=new RegExp("\\.("+aS.join("|")+")$","i");return aR.test(aO)}function ae(aP){var aR=aP.target||aP.srcElement;if(!aR){return false}if(aR.nodeType==3){aR=aR.parentNode}function aQ(aS){return aS.nodeName.toString().toLowerCase()}var aO=aQ(aR);while(aR.parentNode&&aR.parentNode.nodeName&&((aO!="a"&&aO!="area")||!aR.href)){aR=aR.parentNode;aO=aQ(aR)}if(!aR.href){return false}return aR}function aK(aO,aQ){function aP(aR){return aR?aR.replace(/^www\./,""):""}return aP(aO)==aP(aQ)?true:false}function ai(aQ,aP){if(!aQ||!aP){if(!aQ&&!aP){return true}return false}function aR(aS){return aS.split(":")[0]}function aO(aS){aS=aS.split(":");aS[0]="";aS=aS.join(":").replace(/^\/*/,"");aS=aS.replace(/^www\./,"");return aS.split("/")[0]}if(aR(aQ)!=aR(aP)){return false}if(aO(aQ)==aO(aP)){return true}return false}function N(aR,aQ){var aS=aQ.target,aO=false;if(!aQ.hostname){return false}if(!aS||aS=="_self"||aS=="_top"||aS=="_parent"){aO=true}var aP=aR.shiftKey||aR.ctrlKey||aR.altKey;if(!aP){if(aR.modifiers&&I.Event){aP=aR.modifiers&I.Event.CONTROL_MASK||aR.modifiers&I.Event.SHIFT_MASK||aR.modifiers&I.Event.ALT_MASK}}return aO&&!aP}function T(aP,aW,aV,aY,aR){aR=aR||{};var aT=(typeof aV!="undefined")?aV:(aI===null?u.href:aI),aQ=[];function aX(a0,aZ){aQ[aQ.length]=a0;aQ[aQ.length]=aZ}if(aR.ar&&!aR.onlyData){aT=av(aT);aP=av(aP)}aX("page-ref",ac(aT,j));aX("page-url",ac(aP,j));aX("browser-info",at(aW,aR));if(typeof aR.ut!="undefined"){aX("ut",ac(""+aR.ut,y))}if(aY){aX("site-info",ac(i(aY),C))}if(aR.saveRef){aI=aT}var aO=c(aF,aQ);if(I.name!="MetrikaPlayer"){var aU=new Image();var aS=setTimeout(function(){aU.onload=aU.onerror=null;n=false},3000);aU.onload=aU.onerror=function(){clearTimeout(aS);n=true};aU.src=aO;if(aR.isDelay){an(aR.delay)}}return aO}function c(aS,aT){var aR=["rn",ay(),"cnt-class",aG].concat(aT),aO=[];for(var aP=0;aP<aR.length;aP+=2){var aQ=aR[aP+1];if(aQ){aO[aO.length]=aR[aP]+"="+aQ}}return t+aS+aq+"?"+aO.join("&")}function av(aP){var aS=u.host,aO=u.href;if(!aP){return aO}if(aP.search(/^\w+:\/\//)!=-1){return aP}var aR=aP.charAt(0);if(aR=="?"){var aQ=aO.search(/\?/);if(aQ==-1){return aO+aP}return aO.substr(0,aQ)+aP}if(aR=="#"){var aQ=aO.search(/#/);if(aQ==-1){return aO+aP}return aO.substr(0,aQ)+aP}if(aR=="/"){var aQ=aO.search(aS);if(aQ!=-1){return aO.substr(0,aQ+aS.length)+aP}}else{var aT=aO.split("/");aT[aT.length-1]=aP;return aT.join("/")}return aP}var X=null,ag=null;function at(aV,aP){aP=aP||{};var aW=[];function aX(aY,aZ){if(aY&&aZ){aW[aW.length]=[aY,aZ].join(":")}}function aT(aY){aX(aY,aP[aY]?"1":"")}var aR=aa(),aU=Y();if(!z){z=aU;v=aR}aX("j",H.javaEnabled()?"1":"");aX("s",screen.width+"x"+screen.height+"x"+(screen.colorDepth?screen.colorDepth:screen.pixelDepth));if(X===null){X=aJ()}aX("f",X);aX("w",V()+"x"+aB());aX("z",aR);aX("i",aU);if(ag===null){ag=ax()}aX("l",ag||"");aX("en",af()||"");aX("v",x);aX("c",H.cookieEnabled?"1":"");aX("oc",I.ya_cid?"1":"");aX("hid",s);var aO=["ar","ln","fo","dl","ad","nb","pl","pa","ev"];for(var aS=0;aS<aO.length;aS++){aT(aO[aS])}var aQ;if(typeof aV=="undefined"){aQ=Z();aQ=aQ?ac(aQ,J):""}else{aQ=ac(aV,J)}aX("t",aQ);return aW.join(":")}function af(){var aS="",aR=g.getElementsByTagName("meta");if(aR&&aR.length>0){for(var aP=0,aO=aR.length;aP<aO;aP++){if(aR[aP].content){var aQ=aR[aP].content.match(/charset=(.*)/);if(aQ){aS=aQ[1];break}}}}else{aS=g.characterSet||g.charset}return aS}function aJ(){var aR=null,aV=null,aP,aO=I.navigator,aQ="application/x-shockwave-flash",aT="Shockwave Flash",aU="ShockwaveFlash.ShockwaveFlash";if(typeof aO.plugins!="undefined"&&typeof aO.plugins[aT]=="object"){aR=aO.plugins[aT].description;if(aR&&!(typeof aO.mimeTypes!="undefined"&&aO.mimeTypes[aQ]&&!aO.mimeTypes[aQ].enabledPlugin)){aV=aR.replace(/([a-zA-Z]|\s)+/,"").replace(/(\s+r|\s+b[0-9]+)/,".")}}else{if(typeof I.ActiveXObject!="undefined"){try{aP=new ActiveXObject(aU);if(aP){aR=aP.GetVariable("$version");if(aR){aV=aR.split(" ")[1].replace(/,/g,".").replace(/[^.\d]/g,"")}}}catch(aS){}}}return aV}function Z(){var aP=g.title;if(typeof aP!="string"){var aO=g.getElementsByTagName("title");if(aO&&aO.length){aP=aO[0].innerHTML}else{aP=""}}return aP}function ax(){var aO=null;if(I.ActiveXObject){try{var aT=new ActiveXObject("AgControl.AgControl");function aU(aY,aW,aV,aX){while(aQ(aY,aW)){aW[aV]+=aX}aW[aV]-=aX}function aQ(aW,aV){return aW.isVersionSupported(aV[0]+"."+aV[1]+"."+aV[2]+"."+aV[3])}var aP=[1,0,0,0];aU(aT,aP,0,1);aU(aT,aP,1,1);aU(aT,aP,2,10000);aU(aT,aP,2,1000);aU(aT,aP,2,100);aU(aT,aP,2,10);aU(aT,aP,2,1);aU(aT,aP,3,1);aO=aP.join(".")}catch(aS){}}else{var aR=H.plugins["Silverlight Plug-In"];if(aR){aO=aR.description}}return aO}function aa(){return(new Date()).getTimezoneOffset()*(-1)}function Y(){function aQ(aT){return aT<10?"0"+aT:aT}var aP=new Date(),aO=[aP.getFullYear(),aP.getMonth()+1,aP.getDate(),aP.getHours(),aP.getMinutes(),aP.getSeconds()],aS="";for(var aR=0;aR<aO.length;aR++){aS+=aQ(aO[aR])}return aS}function V(){var aO=-1;if(I.innerWidth){aO=parseInt(I.innerWidth)}else{if(g.documentElement&&g.compatMode=="CSS1Compat"){aO=g.documentElement.clientWidth}else{if(g.body){aO=g.body.clientWidth}}}return aO}function aB(){var aO=-1;if(I.innerHeight){aO=parseInt(I.innerHeight)}else{if(g.documentElement&&g.compatMode=="CSS1Compat"){aO=g.documentElement.clientHeight}else{if(g.body){aO=g.body.clientHeight}}}return aO}function aL(aO){return(aO==1&&I.Ya&&I.Ya.Direct)?true:false}function am(){var aO=aq+":"+aG;if(I.ya_hit_param[aO]){return false}if(aq){Ya._metrikaCounters=Ya._metrikaCounters||{};Ya._metrikaCounters[aO]=az;I.ya_hit_param[aO]=1;if(!O){T(u.href,Z(),g.referrer,ab,{ut:ak,ad:aL(aG),saveRef:1})}aj()}if(ap){if(ap.enableAll){az.enableAll()}else{if(ap.clickmap){az.clickmap(ap.clickmap)}if(ap.trackLinks){az.trackLinks(ap.trackLinks)}if(ap.accurateTrackBounce){az.accurateTrackBounce(ap.accurateTrackBounce)}}}if(!O&&A){az._webvisor=true;new A(aq,aG)}}az.reachGoal=function(aQ,aS){var aO=aQ?"goal://"+g.domain+"/"+aQ:u.href,aR=Z(),aP=aQ?u.href:g.referrer;T(aO,aR,aP,aS,{ar:1,isDelay:aQ?true:false,delay:E});return true};var ar;function S(aO){var aP={delay:d};switch(typeof aO){case"string":aP.on=true;break;case"object":aP.on=true;aP.delay=typeof aO.delay!="number"?d:aO.delay;break;case"boolean":aP.on=aO;break;default:return;break}ar=aP}az.trackLinks=S;function aj(){S(false);W(g,"click",function(aO){if(ar.on){aA(aO)}})}function aA(aP){var aT=ae(aP);if(!aT){return}var aU=false;var aR=aM(aT.href);if(r.test(aR)||ao(aR,al)){aU=true}function aO(aX){var aY=U(aT);T(aT.href,aT.href==aY?"":aY,u.href,null,aX)}var aV=aT.className,aW=(aV&&aV.search(/-ym-disable-tracklink/)!=-1)?true:false,aQ=(aV&&aV.search(/-ym-external-link/)!=-1)?true:false;if(aW){return}var aS={ln:true,pl:aN(aT),dl:aU,isDelay:N(aP,aT),delay:ar.delay};if(aQ){aO(aS);return}if(aK(u.hostname,aT.hostname)){if(aU){aS.ln=false;aO(aS)}}else{if(aT.href&&aT.href.search(/^ *javascript:/i)!=-1){return}aO(aS)}}function aw(aO){return;T(target.action,"",u.href,null,{ln:true,isDelay:false,delay:ar.delay})}az.hit=function(aO,aS,aP,aR,aQ){if(aO){T(aO,aS,aP,aR,{ut:aQ,ar:1,saveRef:1})}};az.event=function(aO,aR,aP,aQ){if(aO){T(aO,aR,aP,aQ,{ar:1,ev:1})}};az.params=function(aO){if(aO){T("","","",aO,{ar:1,pa:1,onlyData:1})}};az.file=function(aO,aR,aP,aQ){if(aO){T(aO,"",u.href,aQ,{ar:1,ln:1,dl:1})}};az.extLink=function(aO,aR,aP,aQ){if(aO){T(aO,"",u.href,aQ,{ar:1,ln:1})}};az.notBounce=function(){T("","","",null,{ar:1,nb:1,onlyData:1})};var al=[];az.addFileExtension=function(aO){if(typeof aO=="string"){al.push(aO)}else{al=al.concat(aO)}};az.clickmap=function(aP){var aO="_clickmap";if(az[aO]){az[aO].updateStatus(aP)}else{az[aO]=new aC(aP)}};function aD(a1,aU){var a2=false,aO=false,aZ=true,aT=0,aR=aE(),aQ=null,aV=false;function aW(){if(aV){return}if(aQ){clearTimeout(aQ)}var a4=aU-a0();if(a4<0){a4=0}aQ=setTimeout(function(){aV=true;aX(false);a1()},a4)}function aP(){aO=true;a2=true;aZ=true;aT+=aE()-aR;aR=aE();aW()}function aY(){if(!a2&&!aO){aT=0}aR=aE();aO=true;a2=true;aZ=false;aW()}function aS(){if(!aO){a2=true;aZ=false;aO=true;aW()}}function a0(a4){if(aZ){return aT}return aT+aE()-aR}var a3=[I,"blur",aP,I,"focus",aY,g,"click",aS,g,"mousemove",aS,g,"keydown",aS,g,"scroll",aS];function aX(a5){for(var a4=0;a4<a3.length;a4+=3){if(a5){W(a3[a4],a3[a4+1],a3[a4+2])}else{P(a3[a4],a3[a4+1],a3[a4+2])}}}aX(true);aW()}var aH=false;az.accurateTrackBounce=function(aP){if(aH){return}aH=true;if(ai(g.referrer,u.href)){return}if(typeof aP!="number"){aP=l}function aO(){az.notBounce()}if(m){setTimeout(aO,aP)}else{aD(aO,aP)}};az.audio=function(aP,aQ,aO,aR){};az.video=function(aP,aQ,aO,aR){};az.enableAll=function(){az.trackLinks(true);az.clickmap(true);az.accurateTrackBounce()};function aC(aX){var a4=this,bl=128,aZ=50,a0=1000,be=2,aP=0,aR=null;var a8=["A","B","BIG","BODY","BUTTON","DD","DIV","DL","DT","EM","FIELDSET","FORM","H1","H2","H3","H4","H5","H6","HR","I","IMG","INPUT","LI","OL","P","PRE","SELECT","SMALL","SPAN","STRONG","SUB","SUP","TABLE","TBODY","TD","TEXTAREA","TFOOT","TH","THEAD","TR","U","UL","ABBR","AREA","BLOCKQUOTE","CAPTION","CENTER","CITE","CODE","CANVAS","DFN","EMBED","FONT","INS","KBD","LEGEND","LABEL","MAP","OBJECT","Q","S","SAMP","STRIKE","TT","ARTICLE","AUDIO","ASIDE","FOOTER","HEADER","MENU","METER","NAV","PROGRESS","SECTION","TIME","VIDEO","NOINDEX"];function a3(bo){var bn=bo.parentNode,bp=0;for(var bm=0;bm<bn.childNodes.length;bm++){if(bo.nodeName==bn.childNodes[bm].nodeName){if(bo==bn.childNodes[bm]){return bp}bp++}}return 0}function bc(bn){var bm=aO(bn.nodeName);if(bm=="BODY"||bm=="HTML"){return aU()}return bn.offsetWidth}function aV(bn){var bm=aO(bn.nodeName);if(bm=="BODY"||bm=="HTML"){return a5()}return bn.offsetHeight}function aU(){var bm=g.documentElement,bn=g.body;return Math.max(bm.scrollWidth,bn.scrollWidth,bm.clientWidth)}function a5(){var bm=g.documentElement,bn=g.body;return Math.max(bm.scrollHeight,bn.scrollHeight,bm.clientHeight)}function aY(bn){function bo(bp){var br=0,bq=0;while(bp){br=br+parseInt(bp.offsetTop);bq=bq+parseInt(bp.offsetLeft);bp=bp.offsetParent}return{top:br,left:bq}}function bm(bs){var bv=bs.getBoundingClientRect(),bw=g.body,bq=g.documentElement,bp=I.pageYOffset||bq.scrollTop||bw.scrollTop,bt=I.pageXOffset||bq.scrollLeft||bw.scrollLeft;var bu=bq.clientTop||bw.clientTop||0,bx=bq.clientLeft||bw.clientLeft||0,by=bv.top+bp-bu,br=bv.left+bt-bx;return{top:Math.round(by),left:Math.round(br)}}if(bn.getBoundingClientRect){return bm(bn)}return bo(bn)}function aO(bm){return bm.toString().toUpperCase()}function bf(bm){return bm?bm.replace(/\#.*$/,""):bm}function aQ(bm){if(!bm.which&&bm.button!==p){bm.which=(bm.button&1?1:(bm.button&2?3:(bm.button&4?2:0)))}return bm.which}function a7(bo){var bn=bo.offsetWidth,bm=bo.offsetHeight;return(bn===0&&bm===0)||(bo.style&&bo.style.display==="none")}var aT=";".charCodeAt(0),bk=String.fromCharCode;var a6={},bj={};for(var bd=0;bd<a8.length;bd++){a6[a8[bd]]=bk(aT);bj[bk(aT)]=a8[bd];aT++}this.handler=function(bn){var bm=g.getElementsByTagName("body")[0];if(I.yandex_metrika_disabled_clickmap||(bm&&bm.className&&bm.className.search(/ym-clickmap-ignore/)!=-1)){return}if(a4._prefs.hasQuota){if(!a4._prefs.quota){return}a4._prefs.quota--}a1(bn)};function aW(bm){var bn=a4._prefs.ignoreTags;for(var bo=0;bo<bn.length;bo++){if(aO(bn[bo])==aO(bm)){return true}}return false}function bh(bm){while(bm.parentNode){if(bm.className&&bm.className.search(/ym-clickmap-ignore/)!=-1){return true}bm=bm.parentNode}return false}function ba(bm){var bn="";while(bm.parentNode&&aO(bm.nodeName)!="BODY"&&aO(bm.nodeName)!="HTML"){bn+=a6[bm.nodeName]||"*";bn+=a3(bm)||"";bm=bm.parentNode}return ac(bn,bl)}function a2(){return Math.floor(aE()-h)}function bg(bo){if(bo.pageX==null&&bo.clientX!=null){var bn=g.documentElement,bm=g.body;bo.pageX=bo.clientX+(bn&&bn.scrollLeft||bm&&bm.scrollLeft||0)-(bn.clientLeft||0);bo.pageY=bo.clientY+(bn&&bn.scrollTop||bm&&bm.scrollTop||0)-(bn.clientTop||0)}return{x:bo.pageX,y:bo.pageY}}function aS(bq){var bx=bg(bq),bt=bx.x,bs=bx.y,bo=bq.target||bq.srcElement,bz=a4._prefs,bv=aY(bo),by=65535,bn="",bm=I.location.href;switch(bz.mode){case"fixed":bn="0";if(bb(bo)){bn+="u"}break;case"centered":bn="1";var bw=Math.floor(aU()/2),br=32768;bt=(bt>bw)?bt-bw+br:bt;if(bb(bo)){bn+="u"}break;default:var bu=bc(bo),bp=aV(bo);if(!bu){bu=1}if(!bp){bp=1}bt=Math.floor((bt-bv.left)*by/bu);bs=Math.floor((bs-bv.top)*by/bp);bn=ba(bo);break}if(!bz.withHash){bm=bf(bm)}return c(ad,["page-url",ac(bm,j),"pointer-click","x:"+bt+":y:"+bs+":t:"+Math.floor(a2()/100)+":p:"+bn])}function bb(bm){var bn=aO(bm.nodeName);while(bm.parentNode&&bn!="BODY"&&bn!="HTML"){if(bn=="A"||bn=="INPUT"||bn=="TEXTAREA"){return true}bm=bm.parentNode;bn=bm.nodeName}return false}function bi(bp,bq){if(!bp){return false}var bn=Math.abs(bp.x-bq.x),bm=Math.abs(bp.y-bq.y),bo=bq.time-bp.time;return(bp.dom==bq.dom&&bn<be&&bm<be&&bo<a0)?true:false}function a1(bp){var bm=bp.target||bp.srcElement;if(bm.nodeType==3){bm=bm.parentNode}var bv=aO(bm.nodeName),bu=bg(bp),bn=aQ(bp),bo=2,bs=3;if((bn==bo||bn==bs)&&bv!="A"){return}if(a7(bm)){return}if(bh(bm)||aW(bv)||!a4._prefs.filter(bm,bv)){return}var bq=aE(),bt={dom:bm,x:bu.x,y:bu.y,time:bq};if(bq-aP>aZ){if(a4._prefs.ignoreSameClicks&&bi(aR,bt)){}else{new Image().src=aS(bp);var br=a9(bp);if(br&&N(bp,br)){an(a4._prefs.delay)}}}aP=bq;aR=bt}function a9(bn){var bo=bn.target||bn.srcElement;if(!bo){return false}if(bo.nodeType==3){bo=bo.parentNode}var bm=aO(bo.nodeName);while(bo.parentNode&&bo.parentNode.nodeName&&((bm!="A"&&bm!="AREA")||!bo.href)){bo=bo.parentNode;bm=aO(bo.nodeName)}if(!bo.href){return false}return bo}this.setPrefs=function(bm){function bn(bp,bo){return true}if(typeof bm=="undefined"||bm===false||bm===true){this._prefs={filter:bn,ignoreTags:[],mode:"",delay:d,quota:0,hasQuota:false,withHash:false,ignoreSameClicks:true};return}this._prefs={filter:bm.filter||bn,ignoreTags:bm.ignoreTags||[],mode:bm.mode||"",delay:typeof bm.delay=="undefined"?d:bm.delay,quota:bm.quota||0,hasQuota:!!bm.quota,withHash:!!bm.withHash,ignoreSameClicks:typeof bm.ignoreSameClicks=="undefined"?true:false}};this.updateStatus=function(bm){switch(typeof bm){case"undefined":this.start(true);break;case"boolean":if(bm){this.start(bm)}else{this.stop()}break;case"object":this.start(bm);break}};this._start=false;this.start=function(bm){this.setPrefs(bm);if(!this._start){W(g,"click",this.handler)}this._start=true};this.stop=function(){if(this._start){P(g,"click",this.handler)}this._start=false};this.start(aX)}am()};if(I.ya_cid){new Ya.Metrika(I.ya_cid,I.ya_params,I.ya_class)}if(!I.ya_hit){I.ya_hit=function(c,i){if(I.Ya._yaCounter){I.Ya._yaCounter.reachGoal(c,i)}}}var G="yandex_metrika_callback",M=G+"s",k=I[G],F=I[M];if(typeof k=="function"){k()}if(typeof F=="object"){for(var K=0;K<F.length;K++){var L=F[K];if(L){F[K]=null;L()}}}function q(P){var Q="head",c=g.createElement("script");c.type="text/javascript";c.async=c.defer=true;c.src=t+"//metrika.yandex.ru/js/"+P+"/_loader.js";try{var N=g.getElementsByTagName("html")[0];if(!g.getElementsByTagName(Q)[0]){N.appendChild(g.createElement(Q))}var i=g.getElementsByTagName(Q)[0];i.insertBefore(c,i.firstChild)}catch(O){}}var o="linkmap",b="clickmap",D="ym_playback=",w=I.location.href;if(w.search(D+o)!=-1){q(o)}else{if(w.search(D+b)!=-1){q(b)}}})(this,this.document);