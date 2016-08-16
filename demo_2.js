require('SYBGZBusinessOperationsViewModel','GBLCommonRequest','GBLTGetPindaoRecommBannerRsp','GBLProtocolRequest','GBLProtocolResponse','NSMutableArray','GBLPindaoRecommBanner')
defineClass('SYBGZBusinessOperationsViewModel',{
            loadData:function() {
            self.setStatusLoading();
            var commBannerRequest = require('GBLCommonRequest').alloc().initWithCommand_requestBody_responseClassName(2050,null,require('GBLTGetPindaoRecommBannerRsp').class());
            var weakSelf = __weak(self);
            commBannerRequest.sendWithCompletion(block("BOOL, GBLProtocolRequest *,GBLProtocolResponse *",function(success,request,response) {
                                                       var self = __strong(weakSelf);
                                                       if(!success) {
                                                            self.setStatusFinish();
                                                            return;
                                                        }
                                                       
                                                       var jceObjectV2 = response.rspBody();
                                                       var jceObj = response.rspHead();
                                                       if(!jceObjectV2) {
                                                            self.setStatusFinish();
                                                            return;
                                                       }
                                                       var rsp = jceObjectV2;
                                                       var bannerInfos = rsp.jce__banner__list();
                                                       var self_bannerInfoArr = self.bannerInfoArray();
                                                       
                                                       self.setBannerInfoArray(rsp.jce__banner__list().copy());
                                                       var tmpArray = require('NSMutableArray').alloc().init();
                                                       
                                                       console.log('info count:' + rsp.jce__banner__list().count() + '[js obj:' + self_bannerInfoArr.count() + ']');
                                                       for(var index = 0; index < rsp.jce__banner__list().count(); index ++) {
                                                       tmpArray.addObject(self.bannerInfoArray().objectAtIndex(index).jce__image__url().copy());
                                                       var bannerObj = rsp.jce__banner__list().objectAtIndex(index);
                                                       console.log('image Url' + bannerObj.jce__image__url());
                                                       }
                                                       
                                                       if(tmpArray.count() > 0) {
                                                       self.setImageInfoArray(tmpArray.copy());
                                                       }
                                                       
                                                       self.setIHeight(self.getHeight());
                                                       self.setStatusFinish();
                                                       }));
            } });


/*  发现页样式 */
 require('GBLTableCellModule,SYBChannelRecommendHeaderCell,UIColor,GBLUIJumpHandler,GBLMtaUtil');
 defineClass('GBLRecommendChannelListModule', {
     createRecommendHeadCellModule: function() {
         var module = GBLTableCellModule.alloc().init();
         module.setHeight(75);
         module.setSelctionStyle(0);
         module.setViewClass(SYBChannelRecommendHeaderCell.class());
         module.setViewIdentifier("SYBChannelRecommendHeaderCellV2");
         module.setViewNibName("SYBChannelRecommendHeaderCellV2");

        var weak_self = __weak(self);
         module.setUpdateCell(block("UITableViewCell *,NSIndexPath *, UITableView *, GBLTableCellModule *",function( tCell, indexPath,tableView, module) {

             var self = __strong(self);
             var headerCell = tCell;
             //        headerCell.recommendView().hidden() = indexPath.row() != 0;
             headerCell.headerArrowImageView().setHidden(0);
             headerCell.updatePadding(self.padding());
             headerCell.recommendView().setHidden(1); //产品不需要这个标志了 by fanghaoshu
//             headerCell.setGameName_andGameIcon_andBackgroundColor(self.gameName(), self.gameIcon(), UIColor.redColor());
             headerCell.setSelectionStyle(0);
         }));


         module.setClickCell(block ("NSIndexPath *, UITableView *,GBLTableCellModule *",function( indexPath, tableView,  module) {
             //        @strongify(self);
             var self = __strong(weak_self);
             //TODO:跳转到对应游戏界面
             if (self.gameName().isEqualToString("热门频道")) {
                 GBLUIJumpHandler.sharedInstance().jumpToHotChannelList();
                 return;
             }
             GBLMtaUtil.trackCustomKeyValueEvent_module_props("channel_game_banner_click", "find", block('NSMutableDictionary*', function(propsSet) {
                 propsSet.setObject_forKey((self.gameId()), "game_id");
             }));
             GBLUIJumpHandler.sharedInstance().jumpToGameDtailVC(self.gameId());
         }));

         return module;
     },
 });
