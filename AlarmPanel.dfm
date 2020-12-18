object Form3: TForm3
  Left = 230
  Top = 125
  BorderIcons = [biSystemMenu, biMaximize]
  BorderStyle = bsDialog
  Caption = 'Alarm'
  ClientHeight = 171
  ClientWidth = 386
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 183
    Top = 144
    Width = 22
    Height = 13
    Caption = 'HEX'
  end
  object Label2: TLabel
    Left = 16
    Top = 6
    Width = 39
    Height = 13
    Caption = 'Label2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 8
    Top = 56
    Width = 32
    Height = 13
    Caption = 'Label3'
    Visible = False
  end
  object Edit1: TEdit
    Left = 5
    Top = 30
    Width = 25
    Height = 21
    TabOrder = 0
    Visible = False
  end
  object ClearBttn: TButton
    Left = 16
    Top = 80
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 1
  end
  object NextBitBttn: TBitBtn
    Left = 200
    Top = 80
    Width = 75
    Height = 25
    Caption = 'Next'
    TabOrder = 2
    OnClick = NextBitBttnClick
    Kind = bkRetry
  end
  object AlrmComboBox: TComboBox
    Left = 24
    Top = 115
    Width = 233
    Height = 21
    ItemHeight = 13
    TabOrder = 3
  end
end
