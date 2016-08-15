require('GBLTableCellModule,SYBChannelRecommendHeaderCell,UIColor,GBLUIJumpHandler,GBLMtaUtil');
defineClass('GBLRecommendChannelListModule', {
    createRecommendHeadCellModule: function() {
        var module = GBLTableCellModule.alloc().init();
        module.setHeight(75);
        module.setSelctionStyle(UITableViewCellSelectionStyleNone);
        module.setViewClass(SYBChannelRecommendHeaderCell.class());
        module.setViewIdentifier("SYBChannelRecommendHeaderCellV2");
        module.setViewNibName("SYBChannelRecommendHeaderCellV2");
        
       var weak_self = __weak(self);
        module.setUpdateCell(block("UITableViewCell *,NSIndexPath *, UITableView *, GBLTableCellModule *",function( tCell, indexPath,tableView, module) {
        
            var self = __strong(self);
            var headerCell = tCell;
            //        headerCell.recommendView().hidden() = indexPath.row() != 0;
            headerCell.headerArrowImageView().setHidden(NO);
            headerCell.updatePadding(self.padding());
            headerCell.recommendView().setHidden(YES); //产品不需要这个标志了 by fanghaoshu
            //        headerCell.gameNameLabel().text() = [NSString stringWithFormat:"   %",self.gameName]();
            headerCell.setGameName_andGameIcon_andBackgroundColor(self.gameName(), self.gameIcon(), UIColor.colorFromHexString((self.background().length() > 0 ? self.background() : "#4CBEFF")));
            headerCell.setSelectionStyle(UITableViewCellSelectionStyleNone);
        }));


        module.setClickCell(block ("NSIndexPath *, UITableView *,GBLTableCellModule *",function( indexPath, tableView,  module) {
            //        @strongify(self);
            var self = __strong(weak_self);
            //TODO:跳转到对应游戏界面
            if (self.gameName().isEqualToString("热门频道")) {
                GBLUIJumpHandler.sharedInstance().jumpTotalScoreRankPage();
                return;
            }
            GBLMtaUtil.trackCustomKeyValueEvent_module_props(keyEventID_channel_game_banner_click, KeyModuleID_Find, block('NSMutableDictionary*', function(propsSet) {
                propsSet.setObject_forKey((self.gameId()), "game_id");
            }));
            GBLUIJumpHandler.sharedInstance().jumpToGameDtailVC(self.gameId());
        }));

        return module;
    },
});