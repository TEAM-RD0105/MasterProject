%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                   0105 TEAM TCU CONTROL SOFTWARE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%-------------------------------------------------------------------------
% DESCRIPTION
%-------------------------------------------------------------------------
%   This file sets up the paths and calls the relevant paramater files for
%   the SB CVT Control Software for RD0081 TEAM ATV SB
%------------------------------------------------------------------------- 
% Date Created: 	02/27/2025
% Created by: 		C Romo
% Last Update: 		-
% Updated by:  		- 
%------------------------------------------------------------------------- 
%-------------------------------------------------------------------------

% This script will set up the correct Matlab environment for software
% development and simulation

clc

root = fileparts(mfilename("fullpath"));

genRoot   = fullfile(root,"GeneratedFiles");
cacheRoot = fullfile(genRoot,"Cache");
codeRoot  = fullfile(genRoot,"CodeGen");

Simulink.fileGenControl("set", ...
    "CacheFolder",cacheRoot, ...
    "CodeGenFolder",codeRoot, ...
    "createDir",true);

exclude = ["GeneratedFiles","slprj","_sfprj","_jitprj","tmwinternal", ...
           "ert_rtw","_ert_rtw","codegen",".git","DerivedDataCache"];

p = split(string(genpath(root)), pathsep);
p = p(p ~= "");
p = p(~contains(p, exclude, "IgnoreCase", true));
p = unique(p, "stable");

addpath(strjoin(p, pathsep));

c = dir(fullfile(root,"**","*.c"));
keep = ~contains(string({c.folder}), exclude, "IgnoreCase", true);
c = c(keep);

names = string({c.name});
[unq,~,idx] = unique(lower(names));
counts = accumarray(idx,1);
dup = unq(counts > 1);

if ~isempty(dup)
    warning("Duplicate .c filenames found under repo outside generated folders: %s", ...
        strjoin(dup(1:min(end,10)), ", "));
end

clear root genRoot cacheRoot codeRoot exclude p c keep names unq idx counts dup

% End
