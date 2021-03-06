//
//  TSQCalendarState.h
//  TimesSquare
//
//  Created by Jim Puls on 11/14/12.
//  Licensed to Square, Inc. under one or more contributor license agreements.
//  See the LICENSE file distributed with this work for the terms under
//  which Square, Inc. licenses this file to you.

#import <UIKit/UIKit.h>


typedef NS_ENUM(NSInteger, TSQSelectionMode) {
    TSQSelectionModeSingle,
    TSQSelectionModeMultiple
};


@protocol TSQCalendarViewDelegate;


/** The `TSQCalendarView` class displays a monthly calendar in a self-contained scrolling view. It supports any calendar that `NSCalendar` supports.
 
 The implementation and usage are very similar to `UITableView`: the app provides reusable cells via a data source and controls behavior via a delegate. See `TSQCalendarCell` for a cell superclass.
 */
@interface TSQCalendarView : UIView

/** @name Date Setup */

/** The earliest month the calendar view displays.
 
 Set this property to any `NSDate`; `TSQCalendarView` will only look at the month and year.
 Must be set for the calendar to be useful.
 */
@property (nonatomic, strong) NSDate *firstDate;

/** The latest month the calendar view displays.
 
 Set this property to any `NSDate`; `TSQCalendarView` will only look at the month and year.
 Must be set for the calendar to be useful.
 */
@property (nonatomic, strong) NSDate *lastDate;

/** The first date that can be selected in the calendar view.
 
 Set this property to any `NSDate`; `TSQCalendarView` will disable interaction of cells
 for all dates before the `firstSelectableDate`, If `firstSelectableDate` is before or after
 the bounds of `firstDate` and `lastDate` then this value will be ignored.
 */
@property (nonatomic, strong) NSDate *firstSelectableDate;

/** The selection mode that the calendar supports i.e single or multiple
 
 Set this property to `TSQSelectionModeMultiple` or `TSQSelectionModeSingle`; `TSQSelectionModeMultiple` will allow mutliple selection of dates.
 Defaults to `TSQSelectionModeSingle` single selection.
 */
@property (nonatomic, assign) TSQSelectionMode selectionMode;

/** The currently-selected date on the calendar.
 
 Set this property to any `NSDate`; `TSQCalendarView` will only look at the month, day, and year.
 You can read and write this property. If `calendarView` is configured to `selectionMode` `TSQSelectionModeMultiple` 
 then this property does nothing and returns nil, use `selectedDates` instead.
 */
@property (nonatomic, strong) NSDate *selectedDate;

/** The currently-selected dates on the calendar.
 
 Set this property to an Array of `NSDate` objects; `TSQCalendarView` will only look at the month, day, and year.
 You can read and write this property. If `calendarView` is configured to `selectionMode` `TSQSelectionModeSingle`
 then this property does nothing and returns an empty array, use `selectedDate` instead.
 */
@property (nonatomic, strong) NSArray *selectedDates;

/** @name Calendar Configuration */

/** The calendar type to use when displaying.
 
 If not set, this defaults to `[NSCalendar currentCalendar]`.
 */
@property (nonatomic, strong) NSCalendar *calendar;

/** @name Visual Configuration */

/** The delegate of the calendar view.
 
 The delegate must adopt the `TSQCalendarViewDelegate` protocol.
 The `TSQCalendarView` class, which does not retain the delegate, invokes each protocol method the delegate implements.
 */
@property (nonatomic, weak) id<TSQCalendarViewDelegate> delegate;

/** Whether to pin the header to the top of the view.
 
 If you're trying to emulate the built-in calendar app, set this to `YES`. Default value is `NO`.
 */
@property (nonatomic) BOOL pinsHeaderToTop;

/** Whether or not the calendar snaps to begin a month at the top of its bounds.
 
 This property is roughly equivalent to the one defined on `UIScrollView` except the snapping is to months rather than integer multiples of the view's bounds.
 */
@property (nonatomic) BOOL pagingEnabled;

/** Whether or not the calendar can be scrolled, useful for fixed calendar views.
 
 This property is the equivalent to the one defined on `UIScrollView`.
 */
@property (nonatomic) BOOL scrollingEnabled;

/** Whether or not the calendar bounces, useful for when scrolling is disabled.
 
 This property is the equivalent to the one defined on `UIScrollView`.
 */
@property (nonatomic) BOOL bounces;

/** The distance from the edges of the view to where the content begins.
 
 This property is equivalent to the one defined on `UIScrollView`.
 */
@property (nonatomic) UIEdgeInsets contentInset;

/** The point on the calendar where the currently-visible region starts.
 
 This property is equivalent to the one defined on `UIScrollView`.
 */
@property (nonatomic) CGPoint contentOffset;

/** The cell class to use for month headers.
 
 Since there's very little configuration to be done for each cell, this can be set as a shortcut to implementing a data source.
 The class should be a subclass of `TSQCalendarMonthHeaderCell` or at least implement all of its methods.
 */
@property (nonatomic, strong) Class headerCellClass;

/** The cell class to use for week rows.
 
 Since there's very little configuration to be done for each cell, this can be set as a shortcut to implementing a data source.
 The class should be a subclass of `TSQCalendarRowCell` or at least implement all of its methods.
 */
@property (nonatomic, strong) Class rowCellClass;

/** Scrolls the receiver until the specified date month is completely visible.

 @param date A date that identifies the month that will be visible.
 @param animated YES if you want to animate the change in position, NO if it should be immediate.
 */
- (void)scrollToDate:(NSDate *)date animated:(BOOL)animated;

@end

/** The methods in the `TSQCalendarViewDelegate` protocol allow the adopting delegate to either prevent a day from being selected or respond to it.
 */
@protocol TSQCalendarViewDelegate <NSObject>

@optional

/** @name Responding to Selection */

/** Asks the delegate whether a particular date is selectable.
 
 This method should be relatively efficient, as it is called repeatedly to appropriate enable and disable individual days on the calendar view.
 
 @param calendarView The calendar view that is selecting a date.
 @param date Midnight on the date being selected.
 @return Whether or not the date is selectable.
 */
- (BOOL)calendarView:(TSQCalendarView *)calendarView shouldSelectDate:(NSDate *)date;

/** Tells the delegate that a particular date was selected.
 
 `selectionMode` must be `TSQSelectionModeSingle` for this method to be called.
 
 @param calendarView The calendar view that is selecting a date.
 @param date Midnight on the date being selected.
 */
- (void)calendarView:(TSQCalendarView *)calendarView didSelectDate:(NSDate *)date;

/** Tells the delegate that one of more dates were selected.
 
 `selectionMode` must be `TSQSelectionModeMultiple` for this method to be called.
 
 @param calendarView The calendar view that is selecting a date.
 @param dates Array of selected dates each date being on Midnight.
 */
- (void)calendarView:(TSQCalendarView *)calendarView didSelectDates:(NSArray *)dates;

@end
